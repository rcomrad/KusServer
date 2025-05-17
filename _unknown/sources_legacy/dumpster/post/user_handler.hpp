#ifndef POST_USER_HANDLER_HPP
#define POST_USER_HANDLER_HPP

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#include "post_handler.hpp"

namespace post
{
class UserHandler : public PostHandler
{
public:
    static crow::json::wvalue process(PostRequest<data::User>& aReq) noexcept;

    static crow::json::wvalue rawDataHandler(data::RawData& aData) noexcept;

    static crow::response autorisation(const crow::request& aReq) noexcept;

    static crow::response registration(const crow::request& aReq,
                                       bool aNoConfirmation = false) noexcept;

    // static std::string registration2(const crow::request& aReq,
    //                                    bool info) noexcept;

    static crow::response confirmation(const std::string& aUrl) noexcept;

private:
    static std::mutex mRegMut;

    static void fiil(data::User& aUser) noexcept;

    static std::unordered_map<std::string, std::unordered_set<std::string>>
    getKeyMap() noexcept;
    static bool applyKey(data::User& aUser) noexcept;

    static std::optional<std::string> sendComfLink(
        const data::User& aUser) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_USER_HANDLER_HPP
