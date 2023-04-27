#ifndef POST_USER_HANDLER_HPP
#define POST_USER_HANDLER_HPP

#include <string>

#include "post_handler.hpp"

namespace post
{
class UserHandler : public PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq) noexcept;

    static crow::json::wvalue rawDataHandler(
        std::vector<std::vector<std::string>>& aData,
        const std::vector<std::vector<std::string>>& aAdditionalInfo =
            {}) noexcept;

    static crow::response autorisation(const crow::request& aReq) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_USER_HANDLER_HPP
