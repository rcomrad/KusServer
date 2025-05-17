#include "token_handler.hpp"

#include <cmath>

#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "core/role.hpp"
#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"

#include "pass_generator.hpp"
#include "request_unpacker.hpp"

//--------------------------------------------------------------------------------

serv::TokenHandler& serv::TokenHandler::mInstance =
    serv::TokenHandler::getInstance();

serv::TokenHandler::TokenHandler() noexcept
    : ModuleBase({"token"}),
      //   mIsActive(core::VariableStorage::touchFlag("token_isActive")),
      //   mAuthorizationMemorise(
      //       core::VariableStorage::touchFlag("token_isMemory")),
      mIsActive(core::VariableStorage::touchFlag("token:isActive", false)),
      mAuthorizationMemorise(
          core::VariableStorage::touchFlag("token:isMemory", false)),
      mTokenIterator(1),
      mTokenCount(100)
{
    auto size   = core::VariableStorage::touchInt("token_size", 100);
    mTokenCount = std::max(size, mTokenCount);
    rearrangeTokenArray();

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

    mod::ModuleBase::Command aCommand(
        0, "token", core::VariableStorage::touchWord("token", "turn_off"));
    doAction(aCommand);
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

    auto connection = data::ConnectionManager::getUserConnection();
    auto token =
        connection.val.getData<data::Token>("user_id=" + data::wrap(aUser.id));

    int num = 0;
    if (token.id)
    {
        num = getUserNum(token.value);
    }
    else
    {
        mTokenGenerationMutex.lock();
        do
        {
            if (++mTokenIterator == mTokens.size())
            {
                rearrangeTokenArray();
            }
        } while (mTokens[mTokenIterator].inUse);
        num = mTokenIterator;
        mTokenGenerationMutex.unlock();

        token.userIp    = aIP;
        token.userID    = aUser.id;
        token.startTime = dom::DateAndTime::getCurentTime();
        token.userRole  = aUser.roleID;
        token.value =
            PassGenerator::generate() + "=" + dom::toString(mTokenIterator);
        connection.val.write(token);
    }

    auto& user      = mTokens[num];
    user.inUse      = true;
    user.ip         = token.userIp;
    user.id         = token.userID;
    user.time       = dom::DateAndTime::getTime(token.startTime);
    user.falseLogin = 0;
    user.role       = token.userRole;
    user.password   = token.value;

    return user.password;
}

serv::UserDataPtr
serv::TokenHandler::processNonstatic(const crow::request& aReq) noexcept
{
    serv::UserDataPtr result;

    static std::unordered_set<std::string> withoutAuthentication = {
        "/api/login",
        "/api/registration",
        "/api/confirm",
        "/api/get/if/competition",
        "/api/get_question",
        "/api/post/answer",
        "/api/get/if/competition",
        "/api/get/if/competition_user[competition_id[]]",
        "/api/get/if/competition_question",
        "/api/get/if/competition_question[question_id[id,name]]",
        "/api/command/token/turn_off",
        "/api/dump/*",
        "/api/dump_as_file/*",
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
serv::TokenHandler::doAction(const Command& aCommand) noexcept
{
    std::string res = "No token command applied.";
    if (aCommand.argument == "turn_off")
    {
        res = "Tokens turned OFF!";
        core::VariableStorage::setVariable("token:isActive", false);
        core::VariableStorage::setVariable("token:isMemory", false);
    }
    else if (aCommand.argument == "turn_on")
    {
        res = "Tokens turned ON!";
        core::VariableStorage::setVariable("token:isActive", true);
        core::VariableStorage::setVariable("token:isMemory", false);
    }
    else if (aCommand.argument == "memory")
    {
        res = "Start url-role memorization.";
        core::VariableStorage::setVariable("token:isActive", false);
        core::VariableStorage::setVariable("token:isMemory", true);
    }
    else if (aCommand.argument == "print")
    {
        res = "Print url-role data.";
        printAutorisation();
    }
    else if (aCommand.argument == "cut")
    {
        core::VariableStorage::setVariable("insert_tokens", false);
    }
    else if (aCommand.argument == "add")
    {
        core::VariableStorage::setVariable("insert_tokens", true);
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

    auto userOpt = getUserDataByToken(aToken);
    if (userOpt.has_value())
    {
        auto& user = userOpt.value();

        // if (!dom::DateAndTime::curentTimeAssert(user.time,
        // mTokenLifespan))
        // {
        //     user.inUse = false;
        // }

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

    if (!mIsActive && !result.has_value())
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

    int num = getUserNum(aToken);
    if (num > 0)
    {
        result = mTokens[num];
    }

    return result;
}

int
serv::TokenHandler::getUserNum(const std::string& aToken) noexcept
{
    int result = 0;

    for (int i = aToken.size() - 1; i >= 0 && std::isdigit(aToken[i]); --i)
    {
        result *= 10;
        result += aToken[i] - '0';
    }

    if (result < 1 || result >= mTokens.size())
    {
        result = 0;
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

void
serv::TokenHandler::rearrangeTokenArray() noexcept
{
    mTokens.resize(mTokenCount);
    for (auto& i : mTokens) i.inUse = false;

    auto connection = data::ConnectionManager::getUserConnection();
    auto tokens     = connection.val.getDataArray<data::Token>();
    std::vector<int> toDrop;
    for (auto& i : tokens)
    {
        // if (dom::DateAndTime::curentTimeAssert(i.startTime, mTokenLifespan))
        // {
        //     toDrop.emplace_back(i.id);
        // }
        // else
        {
            int num = getUserNum(i.value);
            // inUse[num] = true;

            mTokens[num].id       = i.userID;
            mTokens[num].role     = i.userRole;
            mTokens[num].ip       = i.userIp;
            mTokens[num].password = i.value;
            mTokens[num].inUse    = true;
            mTokens[num].time     = dom::DateAndTime::getTime(i.startTime);
        }
    }
    connection.val.dropByID("token", toDrop);

    mTokenIterator = 1;

    mTokens[0].id    = 0;
    mTokens[0].role  = 0;
    mTokens[0].inUse = true;
}
