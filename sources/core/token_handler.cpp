#include "token_handler.hpp"

#include <unordered_set>

#include "domain/date_and_time.hpp"

#include "core/role.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "file_data/variable_storage.hpp"

core::TokenHandler::TokenHandler() noexcept
    : mIsActive(true), mAuthorizationSetter(false)
{
    mAlphabet = "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "!\"#$%&\'()*+,-./:;<>?@[\\]^_`{|}~";

    mRandGenerator.seed(0);
    mDistribution = std::move(
        std::uniform_int_distribution<uint32_t>(0, mAlphabet.size() - 1));

    mTokenIterator = 1;

    auto size = file::VariableStorage::getInstance().getInt("token_size");
    if (size.has_value() && size.value() > 1)
    {
        mTokenSize = size.value();
    }
    else
    {
        mTokenSize = 100;
    }
    mTokens = std::make_unique<User[]>(mTokenSize);

    std::vector<int> lifespan = {24, 0, 0};
    auto lifespanInput =
        file::VariableStorage::getInstance().getWord("token_lifespan");
    if (lifespanInput.has_value())
    {
        auto temp = file::Parser::slice(lifespanInput.value(), ":");
        if (temp.size() == 3)
        {
            lifespan.clear();
            for (auto& i : temp)
            {
                lifespan.emplace_back(std::stoi(i));
            }
        }
    }
    mTokenLifespan = {lifespan[0], lifespan[1], lifespan[2]};

    auto com = file::VariableStorage::getInstance().getWord("authentication");
    if (com.has_value())
    {
        executeCommand(com.value());
    }
}

core::TokenHandler&
core::TokenHandler::getInstance() noexcept
{
    static TokenHandler instance;
    return instance;
}

std::string
core::TokenHandler::generate(const data::User& aUser,
                             const std::string& aIP) noexcept
{
    std::string result;
    if (mIsActive)
    {
        mTokenGenerationMutex.lock();

        ++mTokenIterator;
        if (mTokenIterator == mTokenSize)
        {
            mTokenIterator = 1;
        }

        auto& user = mTokens[mTokenIterator];
        const std::lock_guard<std::mutex> lock(user.userMutex);

        mTokenGenerationMutex.unlock();

        user.inUse      = true;
        user.ip         = aIP;
        user.id         = aUser.id;
        user.time       = boost::posix_time::second_clock::local_time();
        user.falseLogin = 0;
        user.role       = aUser.roleID;

        user.password.clear();
        while (user.password.size() < 20)
        {
            int indx = mDistribution(mRandGenerator);
            user.password.push_back(mAlphabet[indx]);
        }

        result = user.password += "=" + dom::toString(mTokenIterator);
    }
    else
    {
        result = "NUN";
    }

    return result;
}

bool
core::TokenHandler::process(const crow::request& aReq) noexcept
{
    bool result = false;

    static std::unordered_set<std::string> withoutAuthentication = {
        "/api/login", "/api/registration"};

    auto tokenOpt = getTokenFromReq(aReq);
    if (tokenOpt.has_value())
    {
        auto& token = tokenOpt.value();
        result      = mAuthorizationSetter
                          ? apply(token, aReq.raw_url)
                          : check(token, aReq.raw_url, aReq.remote_ip_address);
    }
    else if (withoutAuthentication.count(aReq.raw_url) || !mIsActive)
    {
        result = true;
    }

    return result;
}

bool
core::TokenHandler::executeCommand(const std::string& aCommand) noexcept
{
    bool result = true;
    if (aCommand == "turn_off")
    {
        mIsActive            = false;
        mAuthorizationSetter = false;
    }
    else if (aCommand == "turn_on")
    {
        mIsActive            = true;
        mAuthorizationSetter = false;
    }
    else if (aCommand == "memory")
    {
        mIsActive            = false;
        mAuthorizationSetter = true;
    }
    else if (aCommand == "print")
    {
        printAutorisation();
    }
    else
    {
        result = false;
    }
    return result;
}

int
core::TokenHandler::getRoleID(const crow::request& aReq) noexcept
{
    int result = 0;

    auto tokenOpt = getTokenFromReq(aReq);
    if (tokenOpt.has_value())
    {
        auto userOpt = getUserByToken(tokenOpt.value());
        if (userOpt.has_value())
        {
            result = userOpt.value().role;
        }
    }

    return result;
}

std::unordered_set<std::string>
core::TokenHandler::getRoleName(const crow::request& aReq) noexcept
{
    return core::Role::getRoles(getRoleID(aReq));
}

bool
core::TokenHandler::checkAuthorizationStatus() noexcept
{
    return mIsActive;
}

bool
core::TokenHandler::check(const std::string& aToken,
                          const std::string& aURL,
                          const std::string& aIP) noexcept
{
    bool result = !mIsActive;

    if (mIsActive)
    {
        auto userOpt = getUserByToken(aToken);
        if (userOpt.has_value())
        {
            auto& user = userOpt.value();

            const std::lock_guard<std::mutex> lock(user.userMutex);
            if (user.inUse && user.ip == aIP)
            {
                if (dom::DateAndTime::curentTimeAssert(user.time,
                                                       mTokenLifespan))
                {
                    result = true;
                }
                else
                {
                    user.inUse = false;
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

    return result;
}

bool
core::TokenHandler::apply(const std::string& aToken,
                          const std::string& aURL) noexcept
{
    auto roles = file::Parser::slice(aToken, ",");
    roles.emplace_back("admin");
    std::unordered_set<std::string> roleSet(roles.begin(), roles.end());
    mAutorisation[aURL] |= core::Role::getInstance().getRoleID(roleSet);
    return true;
}

void
core::TokenHandler::printAutorisation() const noexcept
{
    std::string data;
    for (auto& i : mAutorisation)
    {
        data += i.first + " " + dom::toString(i.second) + "\n";
    }
    file::File::writeData("config", "url.conf", data);
}

boost::optional<core::TokenHandler::User&>
core::TokenHandler::getUserByToken(const std::string& aToken) noexcept
{
    boost::optional<User&> result;

    int num = 0;
    for (int i = aToken.size() - 1; std::isdigit(aToken[i]); --i)
    {
        num *= 10;
        num += aToken[i] - '0';
    }

    if (num > 0 && num < mTokenSize)
    {
        result = mTokens[num];
    }

    return result;
}

boost::optional<const std::string&>
core::TokenHandler::getTokenFromReq(const crow::request& aReq) noexcept
{
    boost::optional<const std::string&> result;
    auto it = aReq.headers.find("token");
    if (it != aReq.headers.end())
    {
        result = it->second;
    }
    return result;
}

// bool
// core::TokenHandler::isActive() noexcept
// {
//     return mIsActive;
// }
