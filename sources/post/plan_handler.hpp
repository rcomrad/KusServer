#ifndef PLAN_HANDLER_HPP
#define PLAN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string_view>

#include "database/database_query.hpp"

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class PlanHandler : protected PostHandler
{
public:
    static crow::json::wvalue uploadFromFile(const crow::request& aReq,
                                             data::DatabaseQuery& aDBQ);

    static void csvLoad(crow::multipart::message& aMsg,
                        data::DatabaseQuery& aDBQ);

    static void parseDataFile(std::string_view aFileName,
                              data::DatabaseQuery& aDBQ);

private:
    static void make(data::Table<data::Plan>& aPlan, data::DatabaseQuery& aDBQ);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !PLAN_HANDLER_HPP
