#include "token_handler.hpp"

#include <cmath>

#include "domain/date_and_time.hpp"

#include "core/role.hpp"
#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"

#include "pass_generator.hpp"
#include "request_unpacker.hpp"

//--------------------------------------------------------------------------------

serv::TokenHandler& serv::TokenHandler::mInstance = getInstance();

serv::TokenHandler::TokenHandler() noexcept
    : ModuleBase("token", file::Value::Type::String),
      //   mIsActive(core::VariableStorage::touchFlag("token_isActive")),
      //   mAuthorizationMemorise(
      //       core::VariableStorage::touchFlag("token_isMemory")),
      mIsActive(false),
      mAuthorizationMemorise(false),
      mTokenIterator(1)
{
    auto size = core::VariableStorage::touchInt("token_size", 100);
    size      = std::max(size, 10);
    mTokens.resize(size);

    std::vector<int> lifespan = {24, 0, 0};
    auto lifespanInput =
        core::VariableStorage::touchWord("token_lifespan", "24:00:00");
    auto temp = file::Parser::slice(lifespanInput, ":");
    for (int i = 0; i < std::min(temp.size(), size_t(3)); ++i)
    {
        lifespan[i] = std::stoi(temp[i]);
    }
    mTokenLifespan = {lifespan[0], lifespan[1], lifespan[2]};

    auto urlsRoles =
        file::File::getWords("config", "url.conf", file::FileType::File,
                             [](char c) { return c == ' ' || c == '\0'; });
    for (auto& i : urlsRoles)
    {
        mAutorisation[i[0]] = std::stoi(i[1]);
    }

    mTokens[0].id    = 0;
    mTokens[0].role  = 0;
    mTokens[0].inUse = true;
}

serv::TokenHandler&
serv::TokenHandler::getInstance() noexcept
{
    static TokenHandler instance;
    return instance;
}

//--------------------------------------------------------------------------------

std::string
serv::TokenHandler::generate(const data::User& aUser,
                             const std::string& aIP) noexcept
{
    static TokenHandler& instance = getInstance();
    return instance.generateNonstatic(aUser, aIP);
}

serv::UserDataPtr
serv::TokenHandler::process(const crow::request& aReq) noexcept
{
    static TokenHandler& instance = getInstance();
    return instance.processNonstatic(aReq);
}

std::string
serv::TokenHandler::generateNonstatic(const data::User& aUser,
                                      const std::string& aIP) noexcept
{
    std::string result;

    mTokenGenerationMutex.lock();
    if (++mTokenIterator == mTokens.size())
    {
        mTokenIterator = 1;
    }
    mTokenGenerationMutex.unlock();

    auto& user      = mTokens[mTokenIterator];
    user.inUse      = true;
    user.ip         = aIP;
    user.id         = aUser.id;
    user.time       = boost::posix_time::second_clock::local_time();
    user.falseLogin = 0;
    user.role       = aUser.roleID;
    user.password =
        PassGenerator::generate() + "=" + dom::toString(mTokenIterator);

    return user.password;
}

serv::UserDataPtr
serv::TokenHandler::processNonstatic(const crow::request& aReq) noexcept
{
    serv::UserDataPtr result;

    static std::unordered_set<std::string> withoutAuthentication = {
        "/api/login",
        "/api/registration",
        "/api/get/if/competition",
        "/api/get_question",
        "/api/post/answer",
        "/api/get/if/competition",
        "/api/get/if/competition_user[competition_id[]]",
        "/api/get/if/competition_question[question_id[id,name]]",
    };
    auto url      = urlDedaction(aReq.raw_url);
    auto tokenOpt = RequestUnpacker::getToken(aReq);

    if (tokenOpt.has_value())
    {
        auto& token = tokenOpt.value();
        result      = mAuthorizationMemorise
                          ? apply(token, url)
                          : check(token, url, aReq.remote_ip_address);
    }
    // TODO: remove
    if (!result.has_value() && (withoutAuthentication.count(url) || !mIsActive))
    {
        result = &mTokens[0];
    }

    return result;
}

//--------------------------------------------------------------------------------

std::string
serv::TokenHandler::doAction() noexcept
{
    static auto& command =
        core::VariableStorage::touchWord("token", "turn_off");

    std::string res = "No token command applied.";
    if (command == "turn_off")
    {
        res                    = "Tokens turned OFF!";
        mIsActive              = false;
        mAuthorizationMemorise = false;
    }
    else if (command == "turn_on")
    {
        res                    = "Tokens turned ON!";
        mIsActive              = true;
        mAuthorizationMemorise = false;
    }
    else if (command == "memory")
    {
        res                    = "Start url-role memorization.";
        mIsActive              = false;
        mAuthorizationMemorise = true;
    }
    else if (command == "print")
    {
        res = "Print url-role data.";
        printAutorisation();
    }

    return res;
}

void
serv::TokenHandler::printAutorisation() const noexcept
{
    std::string data;
    for (auto& i : mAutorisation)
    {
        data += i.first + " " + dom::toString(i.second) + "\n";
    }
    file::File::writeData("config", "url.conf", data);
}

// int
// serv::TokenHandler::getRoleID(const crow::request& aReq) noexcept
// {
//     int result = 0;

//     auto tokenOpt = getTokenFromReq(aReq);
//     if (tokenOpt.has_value())
//     {
//         auto userOpt = getUserByToken(tokenOpt.value());
//         if (userOpt.has_value())
//         {
//             result = userOpt.value().role;
//         }
//     }

//     return result;
// }

// std::unordered_set<std::string>
// serv::TokenHandler::getRoleName(const crow::request& aReq) noexcept
// {
//     return core::Role::getRoles(getRoleID(aReq));
// }

// bool
// serv::TokenHandler::checkAuthorizationStatus() noexcept
// {
//     return mIsActive;
// }

//--------------------------------------------------------------------------------

serv::UserDataPtr
serv::TokenHandler::check(const std::string& aToken,
                          const std::string& aURL,
                          const std::string& aIP) noexcept
{
    serv::UserDataPtr result;

    if (mIsActive)
    {
        auto userOpt = getUserDataByToken(aToken);
        if (userOpt.has_value())
        {
            auto& user = userOpt.value();

            if (!dom::DateAndTime::curentTimeAssert(user.time, mTokenLifespan))
            {
                user.inUse = false;
            }

            if (user.inUse) // && user.ip == aIP)
            {
                auto it = mAutorisation.find(aURL);
                if (it != mAutorisation.end() && it->second & user.role)
                {
                    result = &user;
                }
            }
            // else
            // {
            //     if (++mTokens[num].falseLogin > 10)
            //     {
            //         mTokens[num].inUse = false;
            //     }
            // }
        }
    }
    else
    {
        result = &mTokens[0];
    }

    return result;
}

serv::UserDataPtr
serv::TokenHandler::apply(const std::string& aToken,
                          const std::string& aURL) noexcept
{
    serv::UserDataPtr result;
    auto userOpt = getUserDataByToken(aToken);
    if (userOpt.has_value())
    {
        result = &userOpt.value();
        mAutorisation[aURL] |= userOpt.value().role;
    }
    else
    {
        result = &mTokens[0];
        mAutorisation[aURL] |= core::Role::getRoleID(aToken + ",admin");
    }
    return result;
}

//--------------------------------------------------------------------------------

boost::optional<serv::UserData&>
serv::TokenHandler::getUserDataByToken(const std::string& aToken) noexcept
{
    boost::optional<UserData&> result;

    int num = 0;
    for (int i = aToken.size() - 1; i >= 0 && std::isdigit(aToken[i]); --i)
    {
        num *= 10;
        num += aToken[i] - '0';
    }

    if (num > 0 && num < mTokens.size())
    {
        result = mTokens[num];
    }

    return result;
}

std::string
serv::TokenHandler::urlDedaction(const std::string& aUrl) noexcept
{
    std::string result = aUrl;
    while (true)
    {
        auto num = result.rfind("/");
        if (num == std::string::npos) break;
        else
        {
            if (std::isdigit(result[num + 1]) ||
                result.find("=", num) != std::string::npos)
            {
                result.resize(num);
            }
            else break;
        }
    }
    return result;
}
