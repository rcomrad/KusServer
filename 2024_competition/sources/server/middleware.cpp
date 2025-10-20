#include "middleware.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "file_data/path.hpp"
#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "core/variable_storage.hpp"
#include "file_data/parser.hpp"

#include "token_handler.hpp"

std::ofstream
get_file()
{
    auto path = file::Path::touchFolder("dump");
    return std::ofstream(path.value() + "req_loger_" + dom::DateAndTime::getCurentTimeSafe() +
                         ".log");
}

void
serv::Middleware::before_handle(crow::request& req,
                                crow::response& res,
                                context& ctx)
{
    static std::ofstream loger = get_file();

    std::stringstream ss;
    ss << crow::method_name(req.method) << " " << req.url;
    for (const auto& header : req.headers)
    {
        std::cout << "  " << header.first << ": " << header.second;
    }
    ss << " " << req.body;

    loger << ss.str() << std::endl;

    while (core::VariableStorage::isLocked());

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

    // if (req.url.size() == 71)
    // {
    //     std::string temp = req.url;
    //     std::string id   = {temp.back()};
    //     temp.resize(temp.size() - 17);
    //     if (temp == "/api/get/if/competition_question[question_id[id,name]]")
    //     {

    //         data::Competition comp;
    //         {
    //             auto connection =
    //             data::ConnectionManager::getUserConnection(); comp =
    //             connection.val.getData<data::Competition>("id=" + id);
    //         }

    //         if (user.value()->id != 2 &&
    //             (comp.id == 0 || !dom::DateAndTime::isPassed(comp.startTime)
    //             ||
    //              dom::DateAndTime::isPassed(comp.endTime)))
    //         {
    //             dom::writeInfo("My id: ", user.value()->id);
    //             crow::json::wvalue result;
    //             result["errors"] = dom::DateAndTime::getCurentTime();
    //             result["competition_question"] = "errors";
    //             res                            = std::move(result);
    //             res.end();
    //         }
    //     }
    // }
    // std::cout << "----->>>>>>>>> " <<  req.url << std::endl;
    std::string temp = req.url;
    auto parts       = file::Parser::slice(temp, "/");

    // if (parts[parts.size() - 2] ==
    // "user_competition[competition_id[id;name;start_time]]")
    // {
    //     parts[parts.size() - 2] = "user_competition[competition_id[]]";
    //     req.url.clear();
    //     for(auto& ii : parts)
    //     {
    //         req.url.push_back('/');
    //         req.url+= ii;
    //     }
    // }
    // https://kussystem.ru/api/get/if/competition_user[competition_id[]]/user_id=2
    // if (parts[parts.size() - 2] ==
    // "user_competition[competition_id[id;name;start_time]]") if
    // (parts[parts.size() - 2] == "competition_user[competition_id[]]") if
    // (parts[parts.size() - 2] == "competition_user[competition_id[]]")
    // {
    //     crow::json::wvalue::list ls;

    //     crow::json::wvalue comp;
    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "ФИНСКИЙ ЯЗЫК(неуглубленный) 5–6 классы";
    //     comp["id"] = 1;

    //     crow::json::wvalue comp2;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "ФИНСКИЙ ЯЗЫК(неуглубленный) 7–8 классы";
    //     comp["id"] = 2;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "ФИНСКИЙ ЯЗЫК(неуглубленный) 9–11 классы";
    //     comp["id"] = 3;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "ФИНСКИЙ ЯЗЫК(углубленный) 5–6 классы";
    //     comp["id"] = 4;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "ФИНСКИЙ ЯЗЫК(углубленный) 7–8 классы";
    //     comp["id"] = 5;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "ФИНСКИЙ ЯЗЫК(углубленный) 9–11 классы";
    //     comp["id"] = 6;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "Гиды-переводчики 7–8 классы";
    //     comp["id"] = 7;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     comp["end_time"] = "2024-10-10 16:00:00";
    //     comp["start_time"] = "2024-10-10 15:00:00";
    //     comp["name"] = "Гиды-переводчики 9–11 классы";
    //     comp["id"] = 8;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     crow::json::wvalue result;
    //     result["competition_users"] = std::move(ls);

    //     res                            = std::move(result);
    //     res.end();
    // }

    //     if (parts[parts.size() - 2] == "competition_user[competition_id[]]")
    // {
    //     crow::json::wvalue::list ls;

    //     crow::json::wvalue comp;
    //     comp["end_time"] = "2024-04-14 14:00:00";
    //     comp["start_time"] = "2024-04-14 10:00:00";
    //     comp["name"] = "ПРограммирование";
    //     comp["id"] = 1;

    //     crow::json::wvalue comp2;
    //     comp2["competition"] = std::move(comp);
    //     ls.push_back(std::move(comp2));

    //     crow::json::wvalue result;
    //     result["competition_users"] = std::move(ls);

    //     res                            = std::move(result);
    //     res.end();
    // }

    // std::cout << "----->>>>>>>>> " <<  req.url << std::endl;
}

void
serv::Middleware::after_handle(crow::request& req,
                               crow::response& res,
                               context& ctx)
{
}
