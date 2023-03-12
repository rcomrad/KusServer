#include "user_handler.hpp"

#include <sstream>

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

crow::json::wvalue
post::UserHandler::uploadFromFile(const crow::request& aReq,
                                  data::DatabaseQuery& aDBQ)
{
    crow::json::wvalue res;

    crow::multipart::message msg(aReq);
    std::string filePath = uploadFile(msg, aDBQ);

    std::string type = msg.get_part_by_name("index").body;
    if (type == "data")
    {
        res = dataFileUpload(filePath, aDBQ);
    }

    return res;
}

crow::json::wvalue
post::UserHandler::dataFileUpload(const std::string& aFilePath,
                                  data::DatabaseQuery& aDBQ)
{
    auto data = dataFileParser<data::User>(aFilePath, 1, {0, 5});

    auto roleTable = aDBQ.getData<data::Role>();
    for (int i = 0; i < data.table.size(); ++i)
    {
        int num = 0;
        std::stringstream ss;
        ss << data.additionalLines[i][0];
        std::string singleRole;
        std::set<std::string> roles;
        while (ss >> singleRole)
        {
            roles.insert(singleRole);
        }

        for (auto& i : roleTable)
        {
            if (roles.count(*(std::string*)i[1]))
            {
                num += 1 << (*(int*)i[0] - 1);
            }
        }
        *(int*)data.table[i][data.table.names["role_id"]] = num;
    }

    aDBQ.update(data.table);

    return {200};
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
