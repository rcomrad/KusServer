#include "token_handler.hpp"

core::TokenHandler::TokenHandler() noexcept
{
    mAlphabet = "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";

    mRandGenerator.seed(0);
    mDistribution = std::move(
        std::uniform_int_distribution<uint32_t>(0, mAlphabet.size() - 1));
}

core::TokenHandler&
core::TokenHandler::getInstance() noexcept
{
    static TokenHandler instance;
    return instance;
}

std::string
core::TokenHandler::generate() noexcept
{
    std::string result;

    mMutex.lock();
    while (true)
    {
        result.clear();
        while (result.size() < 20)
        {
            int indx = mDistribution(mRandGenerator);
            result.push_back(mAlphabet[indx]);
        }
        if (mTokens.find(result) == mTokens.end()) break;
    }

    mTokens[result];

    mMutex.unlock();

    return result;
}

bool
core::TokenHandler::check(const std::string& aToken,
                          const std::string& aURL) noexcept
{
    // const std::lock_guard<std::mutex> lock(mMutex);
    bool result = false;

    mMutex.lock();

    mMutex.unlock();

    return result;
}

void
core::TokenHandler::clear() noexcept
{
    mMutex.lock();
    mTokens.clear();
    mMutex.unlock();
}
