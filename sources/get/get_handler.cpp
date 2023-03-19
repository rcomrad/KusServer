#include "get_handler.hpp"

#include "get_router.hpp"

crow::json::wvalue
get::GetHandler::mainGet(const std::string& aRequest,
                         const std::string& aCondition,
                         data::DBSettings& aDBS) noexcept
{
    crow::json::wvalue result;

    data::DataRequest req(aRequest, aCondition);
    data::DatabaseQuery dbq(aDBS);
    for (const auto& i : req)
    {
        dbq.handSelect(i);
        for (const auto& j : i)
        {
            get::GetRouter::basicRouter(j.trueName, j.rowNumbers, dbq);
        }
        dbq.handClose();
    }

    return result;
}