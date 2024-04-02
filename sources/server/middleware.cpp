#include "middleware.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "core/variable_storage.hpp"
#include "file_data/parser.hpp"

#include "token_handler.hpp"

bool
serv::Middleware::redirection_enabled()
{
    return redirection_flag;
}

// example of redirection method
void
serv::Middleware::emergency_redirection()
{
    std::cout << "Emergency rediraction was successful" << std::endl;
}

void
serv::Middleware::process_comp_question(crow::response& res,
                                        serv::UserData user,
                                        std::string id)
{
    data::Competition comp;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        comp            = connection.val.getData<data::Competition>("id=" + id);
    }

    if (user.id != 2 &&
        (comp.id == 0 || !dom::DateAndTime::isPassed(comp.startTime) ||
         dom::DateAndTime::isPassed(comp.endTime)))
    {
        dom::writeInfo("My id: ", user.id);
        crow::json::wvalue result;
        result["errors"]               = dom::DateAndTime::getCurentTime();
        result["competition_question"] = "errors";
        res                            = std::move(result);
        res.end();
    }
}

void
serv::Middleware::process_comp_user(crow::response& res,
                                    serv::UserData user,
                                    std::string id)
{
    crow::json::wvalue comp;
    comp["end_time"]   = "2024-03-23 23:59:59";
    comp["start_time"] = "2024-03-23 07:00:00";
    comp["name"]       = "Программирование";
    comp["id"]         = 1;

    crow::json::wvalue comp2;
    comp2["competition"] = std::move(comp);

    crow::json::wvalue::list ls;
    ls.push_back(std::move(comp2));

    crow::json::wvalue result;
    result["competition_users"] = std::move(ls);

    res = std::move(result);
    res.end();
}

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

    std::string temp = req.url;
    std::string id   = {temp.back()};
    auto parts       = file::Parser::slice(temp, "/");

    std::unordered_map<std::string,
                       void (serv::Middleware::*)(
                           crow::response&, serv::UserData user, std::string)>
        redirection_of_get = {
            {"competition_question[question_id[id,name]]",
             &serv::Middleware::process_comp_question},
            {"competition_user[competition_id[]]",
             &serv::Middleware::process_comp_user    }
    };

    // example of redirection on handler /api/emergency
    std::unordered_map<std::string, void (serv::Middleware::*)()>
        redirection_of_emergency = {
            {"emergency", &serv::Middleware::emergency_redirection}
    };

    std::string handling_table = parts[parts.size() - 2];
    auto it                    = redirection_of_get.find(handling_table);
    if (this->redirection_enabled())
    {
        if (it != redirection_of_get.end())
        {
            (this->*(it->second))(res, *user.value(), id);
        }
        else
        {
            std::string handling_command = parts[parts.size() - 1];
            auto em = redirection_of_emergency.find(handling_command);
            if (em != redirection_of_emergency.end())
            {
                (this->*(em->second))();
            }
        }
    }
}

void
serv::Middleware::after_handle(crow::request& req,
                               crow::response& res,
                               context& ctx)
{
}
