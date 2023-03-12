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
    struct PlanData
    {
        std::string name;
        int subjectID;
        std::string url;
    };

    static crow::json::wvalue uploadFromFile(const crow::request& aReq,
                                             data::DatabaseQuery& aDBQ);

    static crow::json::wvalue csvFileUpload(const PlanData& aPlanData,
                                            data::DatabaseQuery& aDBQ);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !PLAN_HANDLER_HPP
