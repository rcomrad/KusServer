#ifndef POST_SUBMIT_HANDLER_HPP
#define POST_SUBMIT_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class SubmitHandler : protected PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq) noexcept;

private:
    static std::string getCurentTime() noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_SUBMIT_HANDLER_HPP
