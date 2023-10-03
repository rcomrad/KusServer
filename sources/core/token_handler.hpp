#ifndef TOKEN_HANDLER_HPP
#define TOKEN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "database/database_structures.hpp"

#include "boost/optional.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class TokenHandler
{
public:
    static TokenHandler& getInstance() noexcept;
    std::string generate(const data::User& aUser,
                         const std::string& aIP) noexcept;

    bool process(const crow::request& aReq) noexcept;

    // bool isActive() noexcept;

    bool executeCommand(const std::string& aCommand) noexcept;

    int getRoleID(const crow::request& aReq) noexcept;
    std::unordered_set<std::string> getRoleName(
        const crow::request& aReq) noexcept;

private:
    struct User
    {
        bool inUse = false;
        int id;
        int role;
        std::string ip;
        boost::posix_time::ptime time;
        std::string password;
        int falseLogin;
        std::mutex userMutex;
    };

    TokenHandler() noexcept;

    bool check(const std::string& aToken,
               const std::string& aURL,
               const std::string& aIP) noexcept;

    bool apply(const std::string& aToken, const std::string& aURL) noexcept;
    void printAutorisation() const noexcept;

    std::string mAlphabet;
    std::mt19937 mRandGenerator;
    std::uniform_int_distribution<uint32_t> mDistribution;

    boost::posix_time::time_duration mTokenLifespan;
    std::mutex mTokenGenerationMutex;
    // std::vector<User>::iterator mTokenIterator;
    // std::vector<User> mTokens;
    int mTokenIterator;
    int mTokenSize;
    std::unique_ptr<User[]> mTokens;

    std::unordered_map<std::string, int> mAutorisation;

    // std::mutex mMutex;
    // std::unordered_map<std::string, int> mTokens;

    bool mIsActive;
    bool mAuthorizationSetter;
    // std::unordered_map<std::string, User> mURLs;
    // int mNum;

    boost::optional<User&> getUserByToken(const std::string& aToken) noexcept;
    boost::optional<const std::string&> getTokenFromReq(
        const crow::request& aReq) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
