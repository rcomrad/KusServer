#ifndef MARK_HANDLER_HPP
#define MARK_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class MarkHandler : protected PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !MARK_HANDLER_HPP
