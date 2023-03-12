#include "user_handler.hpp"

crow::json::wvalue
post::UserHandler::process(const crow::request& aReq, data::DatabaseQuery& aDBQ)
{
    auto body    = crow::json::load(aReq.body);
    auto request = parseRequest<data::User>(body);

    auto it = request.other.find("role");
    if (it != request.other.end())
    {

        std::set<std::string> roles;
        for (auto& i : it->second)
        {
            roles.insert(i.s());
        }

        int num    = 0;
        auto table = aDBQ.getData<data::Role>();
        for (auto& i : table)
        {
            if (roles.count(*(std::string*)i[1]))
            {
                num += 1 << (*(int*)i[0] - 1);
            }
        }

        *(int*)request.table.back()[request.table.names["role_id"]] = num;
    }

    auto res = aDBQ.update(request.table);
    return {res};
}

crow::response
post::UserHandler::autorisation(const crow::request& aReq,
                                const data::DBSettings& aDBS)
{
    auto x    = crow::json::load(aReq.body);
    auto resp = crow::response(400);
    if (x)
    {
        data::DatabaseQuery dbq(aDBS);
        auto user        = parseRequest<data::User>(x).table;
        std::string cond = "~login = \'" + user[0].login + "\' AND " +
                           "password = \'" + user[0].password + "\'";
        // TODO:
        // resp = serv::Server::get("user", std::move(cond));
    }
    return resp;
}
