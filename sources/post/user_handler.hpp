#ifndef POST_USER_HANDLER_HPP
#define POST_USER_HANDLER_HPP

#include <mutex>
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

    static bool confirm(const std::string& aUrl) noexcept;

private:
    static void fiil(data::User& aUser) noexcept;
    static bool setRole(data::User& aUser) noexcept;
    static std::string send(const std::string& aEmail) noexcept;

    static std::mutex mRegMut;
    static std::mutex mmConformMut;
    static std::unordered_map<std::string, int> mConformationUrls;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_USER_HANDLER_HPP
