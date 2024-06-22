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

    static std::string generate(const data::User& aUser,
                                const std::string& aIP) noexcept;
    static UserDataPtr process(const crow::request& aReq) noexcept;

protected:
    std::string doAction(const Command& aCommand) noexcept override;

private:
    std::string generateNonstatic(const data::User& aUser,
                                  const std::string& aIP) noexcept;
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
    std::unordered_map<std::string, int> mAutorisation;

    bool processCommandsStatic() noexcept;
    void printAutorisation() const noexcept;

    UserDataPtr check(const std::string& aToken,
                      const std::string& aURL,
                      const std::string& aIP) noexcept;
    UserDataPtr apply(const std::string& aToken,
                      const std::string& aURL) noexcept;

    boost::optional<UserData&> getUserDataByToken(
        const std::string& aToken) noexcept;
    int getUserNum(const std::string& aToken) noexcept;
    static std::string urlDedaction(const std::string& aUrl) noexcept;

    void rearrangeTokenArray() noexcept;
};

} // namespace serv

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
