#include "middleware.hpp"

#include <string>
#include <iostream>

#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "core/variable_storage.hpp"

#include "token_handler.hpp"
#include "file_data/parser.hpp"
void
serv::Middleware::before_handle(crow::request& req,
                                crow::response& res,
                                context& ctx)
{
    while (core::VariableStorage::isLocked())
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

            if (user.value()->id != 2 &&
                (comp.id == 0 || !dom::DateAndTime::isPassed(comp.startTime) ||
                 dom::DateAndTime::isPassed(comp.endTime)))
            {
                dom::writeInfo("My id: ", user.value()->id);
                crow::json::wvalue result;
                result["errors"] = dom::DateAndTime::getCurentTime();
                result["competition_question"] = "errors";
                res                            = std::move(result);
                res.end();
            }
        }
    }
// std::cout << "----->>>>>>>>> " <<  req.url << std::endl;
    std::string temp = req.url;
    auto parts = file::Parser::slice(temp, "/");

    // if (parts[parts.size() - 2] == "user_competition[competition_id[id;name;start_time]]")
    // {
    //     parts[parts.size() - 2] = "user_competition[competition_id[]]";
    //     req.url.clear();
    //     for(auto& ii : parts)
    //     {
    //         req.url.push_back('/');
    //         req.url+= ii;
    //     }
    // }
    if (parts[parts.size() - 2] == "user_competition[competition_id[id;name;start_time]]")
    {
        crow::json::wvalue comp;
        comp["end_time"] = "2024-03-11 21:00:00";
        comp["start_time"] = "2024-03-12 10:00:00";
        comp["name"] = "Тестовое задание";
        comp["id"] = 1;

        crow::json::wvalue comp2;
        comp2["competition"] = std::move(comp);

        crow::json::wvalue::list ls;
        ls.push_back(std::move(comp2));

        crow::json::wvalue result;
        result["user_competitions"] = std::move(ls);

        res                            = std::move(result);
        res.end();
    }


    // std::cout << "----->>>>>>>>> " <<  req.url << std::endl;
}

void
serv::Middleware::after_handle(crow::request& req,
                               crow::response& res,
                               context& ctx)
{
}
