#include "token_handler.hpp"

#include "domain/date_and_time.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "file_data/variable_storage.hpp"

core::TokenHandler::TokenHandler() noexcept
{
    mAlphabet = "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "!\"#$%&\'()*+,-./:;<>?@[\\]^_`{|}~";

    mRandGenerator.seed(0);
    mDistribution = std::move(
        std::uniform_int_distribution<uint32_t>(0, mAlphabet.size() - 1));

    mTokens.resize(4000);
    mTokenIterator = mTokens.begin() + 1;

    mIsActive =
        file::VariableStorage::getInstance().getFlagUnsafe("authorisation");
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
    mTokenGenerationMutex.lock();

    ++mTokenIterator;
    if (mTokenIterator == mTokens.end())
    {
        mTokenIterator = mTokens.begin() + 1;
        for (auto& i : mTokens)
        {
            i.inUse = false;
        }
    }
    auto user = *mTokenIterator;

    mTokenGenerationMutex.unlock();

    user.inUse      = true;
    user.ip         = aIP;
    user.id         = aUser.id;
    user.time       = boost::posix_time::second_clock::local_time();
    user.falseLogin = 0;

    user.password.clear();
    while (user.password.size() < 20)
    {
        int indx = mDistribution(mRandGenerator);
        user.password.push_back(mAlphabet[indx]);
    }

    user.password += "=" + dom::toString(mTokenIterator - mTokens.begin());

    return user.password;
}

bool
core::TokenHandler::check(const std::string& aToken,
                          const std::string& aURL,
                          const std::string& aIP) noexcept
{
    bool result = !mIsActive;

    int num = 0;
    for (int i = aToken.size() - 1; std::isdigit(aToken[i]); --i)
    {
        num *= 10;
        num += aToken[i] - '0';
    }

    if (num > 0 && num < mTokens.size())
    {
        if (mTokens[num].inUse && mTokens[num].ip == aIP)
        {
            if (dom::DateAndTime::curentTimeAssert(mTokens[num].time,
                                                   {24, 0, 0}))
            {
                result = true;
            }
            else
            {
                mTokens[num].inUse = false;
            }
        }
        else
        {
            if (++mTokens[num].falseLogin > 10)
            {
                // mTokens[num].inUse = false;
            }
        }
    }

    return result;
}

bool
core::TokenHandler::isActive() noexcept
{
    return mIsActive;
}
