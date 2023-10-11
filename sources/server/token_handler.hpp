#ifndef TOKEN_HANDLER_HPP
#define TOKEN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "database/database_structures.hpp"

#include "boost/optional.hpp"

#include "user_data.hpp"

//--------------------------------------------------------------------------------

namespace serv
{

using UserDataPtr = boost::optional<const UserData const*>;

class TokenHandler
{
    //--------------------------------------------------------------------------------

public:
    HOLY_TRINITY_SINGLE(TokenHandler);

    static std::string generate(const data::User& aUser,
                                const std::string& aIP) noexcept;
    static UserDataPtr process(const crow::request& aReq) noexcept;

    void printAutorisation() const noexcept;

private:
    std::string generateNonstatic(const data::User& aUser,
                                  const std::string& aIP) noexcept;
    UserDataPtr processNonstatic(const crow::request& aReq) noexcept;

    //--------------------------------------------------------------------------------

private:
    TokenHandler() noexcept;
    static TokenHandler& getInstance() noexcept;

    bool& mIsActive;
    bool& mAuthorizationMemorise;

    std::mutex mTokenGenerationMutex;
    boost::posix_time::time_duration mTokenLifespan;
    int mTokenIterator;
    std::vector<UserData> mTokens;
    std::unordered_map<std::string, int> mAutorisation;

    UserDataPtr check(const std::string& aToken,
                      const std::string& aURL,
                      const std::string& aIP) noexcept;
    UserDataPtr apply(const std::string& aToken,
                      const std::string& aURL) noexcept;

    boost::optional<UserData&> getUserDataByToken(
        const std::string& aToken) noexcept;
    static std::string urlDedaction(const std::string& aUrl) noexcept;
};

} // namespace serv

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
