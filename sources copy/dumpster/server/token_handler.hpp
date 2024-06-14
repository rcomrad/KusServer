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
                                const str::String& aIP) noexcept;
    static UserDataPtr process(const crow::request& aReq) noexcept;

protected:
    str::String doAction(const Command& aCommand) noexcept override;

private:
    str::String generateNonstatic(const data::User& aUser,
                                  const str::String& aIP) noexcept;
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

    UserDataPtr check(const str::String& aToken,
                      const str::String& aURL,
                      const str::String& aIP) noexcept;
    UserDataPtr apply(const str::String& aToken,
                      const str::String& aURL) noexcept;

    boost::optional<UserData&> getUserDataByToken(
        const str::String& aToken) noexcept;
    int getUserNum(const str::String& aToken) noexcept;
    static str::String urlDedaction(const str::String& aUrl) noexcept;

    void rearrangeTokenArray() noexcept;
};

} // namespace serv

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
