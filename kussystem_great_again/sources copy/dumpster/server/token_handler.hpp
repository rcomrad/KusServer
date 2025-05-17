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
#include "module/module_base.hpp"

#include "user_data.hpp"

//--------------------------------------------------------------------------------

namespace serv
{

using UserDataPtr = boost::optional<const UserData*>;

class TokenHandler : public mod::ModuleBase
{
    //--------------------------------------------------------------------------------

public:
    HOLY_TRINITY_SINGLE(TokenHandler);

    static str::String generate(const data::User& aUser,
                                const char* aIP) noexcept;
    static UserDataPtr process(const crow::request& aReq) noexcept;

protected:
    str::String doAction(const Command& aCommand) noexcept override;

private:
    str::String generateNonstatic(const data::User& aUser,
                                  const char* aIP) noexcept;
    UserDataPtr processNonstatic(const crow::request& aReq) noexcept;

    //--------------------------------------------------------------------------------

private:
    static serv::TokenHandler& mInstance;
    TokenHandler() noexcept;
    static TokenHandler& getInstance() noexcept;

    const bool& mIsActive;
    const bool& mAuthorizationMemorise;

    std::mutex mTokenGenerationMutex;
    boost::posix_time::time_duration mTokenLifespan;
    int mTokenIterator;
    int mTokenCount;
    std::vector<UserData> mTokens;
    std::unordered_map<str::String, int> mAutorisation;

    bool processCommandsStatic() noexcept;
    void printAutorisation() const noexcept;

    UserDataPtr check(const char* aToken,
                      const char* aURL,
                      const char* aIP) noexcept;
    UserDataPtr apply(const char* aToken, const char* aURL) noexcept;

    boost::optional<UserData&> getUserDataByToken(const char* aToken) noexcept;
    int getUserNum(const char* aToken) noexcept;
    static str::String urlDedaction(const char* aUrl) noexcept;

    void rearrangeTokenArray() noexcept;
};

} // namespace serv

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
