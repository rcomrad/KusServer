#ifndef PLAN_HANDLER_HPP
#define PLAN_HANDLER_HPP

//--------------------------------------------------------------------------------

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

    static crow::json::wvalue uploadFromFile(const crow::request& aReq);

    static crow::json::wvalue csvFileUpload(const PlanData& aPlanData);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !PLAN_HANDLER_HPP
