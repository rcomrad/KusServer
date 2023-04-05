#include "user_handler.hpp"

#include <sstream>

#include "database/connection_manager.hpp"

#include "get/get_handler.hpp"

crow::json::wvalue
post::UserHandler::process(const crow::request& aReq)
{
    auto body    = crow::json::load(aReq.body);
    auto request = parseRequest<data::User>(body);

    // //TODO: move somevere
    //     int tt;
    //     for (auto& i : request.manyToMany)
    //     {
    //         transmitToMTMHandler(i.first, tt, request.other.count("add"),
    //                              i.second);
    //     }

    auto it         = request.other.find("role");
    auto connection = data::ConnectionManager::getUserConnection();
    if (it != request.other.end())
    {

        std::set<std::string> roles;
        for (auto& i : it->second)
        {
            roles.insert(i.s());
        }

        int num    = 0;
        auto table = connection.val.getData<data::Role>();
        for (auto& i : table)
        {
            if (roles.count(*(std::string*)i[1]))
            {
                num += 1 << (*(int*)i[0] - 1);
            }
        }

        *(int*)request.table.back()[request.table.names["role_id"]] = num;
    }

    auto res = connection.val.update(request.table);

    manyToManyTransmiter(request);

    return {res};
}

crow::json::wvalue
post::UserHandler::uploadFromFile(const crow::request& aReq)
{
    crow::json::wvalue res;

    crow::multipart::message msg(aReq);
    std::string filePath = uploadFile(msg);

    std::string type = msg.get_part_by_name("index").body;
    if (type == "data")
    {
        res = dataFileUpload(filePath);
    }

    return res;
}

// TODO: static roles!
crow::json::wvalue
post::UserHandler::dataFileUpload(const std::string& aFilePath)
{
    auto data = dataFileParser<data::User>(aFilePath, 1, {0, 5});

    data::Table<data::Role> roleTable;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        roleTable       = connection.val.getData<data::Role>();
    }

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
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.update(data.table);
    }
    return {200};
}

crow::response
post::UserHandler::autorisation(const crow::request& aReq)
{
    auto x    = crow::json::load(aReq.body);
    auto resp = crow::response(400);
    if (x)
    {
        // data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
        auto user        = parseRequest<data::User>(x).table;
        std::string cond = "login = \'" + user[0].login + "\' AND " +
                           "password = \'" + user[0].password + "\'";
        // TODO:
        auto userJson = get::GetHandler::singlGet("user", std::move(cond));
        if (userJson.t() != crow::json::type::Null)
        {
            resp = userJson;
        }
        else
        {
            resp = crow::response(401);
        }
    }
    // resp = crow::response(401);
    return resp;
}
