#include "token_handler.hpp"

#include "core/program_state.hpp"
#include "file/file.hpp"

core::TokenHandler::TokenHandler() noexcept
{
    mAlphabet = "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";

    mRandGenerator.seed(0);
    mDistribution = std::move(
        std::uniform_int_distribution<uint32_t>(0, mAlphabet.size() - 1));

    auto urls = file::File::getWords("url.conf");
    for (auto& i : urls)
    {
        mURLs[i[0]];
    }

    auto& state = core::ProgramState::getInstance();
    mIsActive   = state.checkFlag(core::Flag::Authorisation);
}

core::TokenHandler&
core::TokenHandler::getInstance() noexcept
{
    static TokenHandler instance;
    return instance;
}

std::string
core::TokenHandler::generate(const data::User& aUser) noexcept
{
    std::string result = std::to_string(aUser.roleID);

    // mMutex.lock();
    // while (true)
    // {
    //     result.clear();
    //     while (result.size() < 20)
    //     {
    //         int indx = mDistribution(mRandGenerator);
    //         result.push_back(mAlphabet[indx]);
    //     }
    //     if (mTokens.find(result) == mTokens.end()) break;
    // }

    // mTokens[result];

    // mMutex.unlock();

    return result;
}

bool
core::TokenHandler::check(const std::string& aToken,
                          const std::string& aURL) noexcept
{
    // const std::lock_guard<std::mutex> lock(mMutex);
    bool result = !mIsActive;

    // mMutex.lock();
    // mMutex.unlock();

    int tole_id = std::stoi(aToken);
    if (mURLs[aURL] & tole_id) result = true;

    return result;
}

void
core::TokenHandler::clear() noexcept
{
    // mMutex.lock();
    // mTokens.clear();
    // mMutex.unlock();
}

bool
core::TokenHandler::isActive() noexcept
{
    return mIsActive;
}
