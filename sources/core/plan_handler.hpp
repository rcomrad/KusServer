#ifndef PLAN_HANDLER_HPP
#define PLAN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string_view>

#include "database/database_query.hpp"

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class PlanHandler : protected PostHandler
{
public:
    // void process(const crow::json::rvalue& req, data::DatabaseQuery& aDBQ);
    static void loadFromFile(std::string_view aFileName, data::DatabaseQuery& aDBQ);
    static void loadFromRequest(const crow::request& aReq, data::DatabaseQuery& aDBQ);

private:
    static void make(data::Table<data::Plan>& aPlan, data::DatabaseQuery& aDBQ);
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !PLAN_HANDLER_HPP
