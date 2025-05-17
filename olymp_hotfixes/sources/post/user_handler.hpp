#ifndef POST_USER_HANDLER_HPP
#define POST_USER_HANDLER_HPP

#include <string>

#include "post_handler.hpp"

namespace post
{
class UserHandler : public PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq);
    static crow::json::wvalue uploadFromFile(const crow::request& aReq);
    static crow::json::wvalue dataFileUpload(const std::string& aFilePath);

    static crow::response autorisation(const crow::request& aReq);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_USER_HANDLER_HPP
