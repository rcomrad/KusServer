#include "middleware.hpp"

#include <string>

#include "domain/date_time.hpp"

#include "database/connection_manager.hpp"

#include "domain/variable_storage.hpp"

#include "token_handler.hpp"

void
serv::Middleware::before_handle(crow::request& req,
                                crow::response& res,
                                context& ctx)
{
    while (dom::VariableStorage::isLocked())
        ;

    auto user = serv::TokenHandler::process(req);
    if (user.has_value())
    {
        ctx.mUser = user.value();
    }
    else
    {
        res.code = 403;
        res.end();
    }

    if (req.url.size() == 71)
    {
        std::string temp = req.url;
        std::string id   = {temp.back()};
        temp.resize(temp.size() - 17);
        if (temp == "/api/get/if/competition_question[question_id[id,name]]")
        {

            data::Competition comp;
            {
                auto connection = data::ConnectionManager::getUserConnection();
                comp = connection.val.getData<data::Competition>("id=" + id);
            }

            // if (user.value()->id != 2 &&
            //     (comp.id == 0 || !dom::DateTime::isPassed(comp.startTime) ||
            //      dom::DateTime::isPassed(comp.endTime)))
            // {
            //     LOG_INFO("My id: ", user.value()->id);
            //     crow::json::wvalue result;
            //     result["errors"] = dom::DateTime::getTimeOnly();
            //     result["competition_question"] = "errors";
            //     res                            = std::move(result);
            //     res.end();
            // }
        }
    }
}

void
serv::Middleware::after_handle(crow::request& req,
                               crow::response& res,
                               context& ctx)
{
}
