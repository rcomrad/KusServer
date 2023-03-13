#ifndef MARK_HANDLER_HPP
#define MARK_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string_view>
#include <vector>

#include "database/database_query.hpp"

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class MarkHandler : protected PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq,
                                      data::DatabaseQuery& aDBQ);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !MARK_HANDLER_HPP
