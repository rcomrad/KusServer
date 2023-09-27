#ifndef TOKEN_HANDLER_HPP
#define TOKEN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "database/database_structures.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class TokenHandler
{
public:
    static TokenHandler& getInstance() noexcept;
    std::string generate(const data::User& aUser,
                         const std::string& aIP) noexcept;
    bool check(const std::string& aToken,
               const std::string& aURL,
               const std::string& aIP) noexcept;

    bool isActive() noexcept;

private:
    struct User
    {
        bool inUse = false;
        int id;
        std::string ip;
        boost::posix_time::ptime time;
        std::string password;
        int falseLogin;
    };

    TokenHandler() noexcept;

    std::string mAlphabet;
    std::mt19937 mRandGenerator;
    std::uniform_int_distribution<uint32_t> mDistribution;

    std::mutex mTokenGenerationMutex;
    std::vector<User>::iterator mTokenIterator;
    std::vector<User> mTokens;

    // std::mutex mMutex;
    // std::unordered_map<std::string, int> mTokens;

    bool mIsActive;
    // std::unordered_map<std::string, User> mURLs;
    // int mNum;
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
