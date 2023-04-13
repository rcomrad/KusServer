#ifndef TOKEN_HANDLER_HPP
#define TOKEN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <random>
#include <string>
#include <unordered_map>

#include "database/database_structures.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class TokenHandler
{
public:
    static TokenHandler& getInstance() noexcept;
    std::string generate(const data::User& aUser) noexcept;
    bool check(const std::string& aToken, const std::string& aURL) noexcept;
    void clear() noexcept;

    bool isActive() noexcept;

private:
    TokenHandler() noexcept;

    std::string mAlphabet;
    std::mt19937 mRandGenerator;
    std::uniform_int_distribution<uint32_t> mDistribution;

    // std::mutex mMutex;
    // std::unordered_map<std::string, int> mTokens;

    bool mIsActive;
    std::unordered_map<std::string, int> mURLs;
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
