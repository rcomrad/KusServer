#include "user_handler.hpp"

#include <sstream>

#include "database/connection_manager.hpp"

#include "core/role.hpp"
#include "core/token_handler.hpp"
#include "get/get_handler.hpp"

crow::json::wvalue
post::UserHandler::process(PostRequest<data::User>& aReq) noexcept
{
    // //TODO: move somevere
    //     int tt;
    //     for (auto& i : request.manyToMany)
    //     {
    //         transmitToMTMHandler(i.first, tt, request.other.count("add"),
    //                              i.second);
    //     }

    auto it = aReq.leftovers.find("role");
    if (it != aReq.leftovers.end())
    {
        std::set<std::string> roles;
        for (auto& i : it->second)
        {
            roles.insert(i.s());
        }

        aReq.data.role_id = core::Role::getInstance().getRoleID(roles);
    }
    aReq.leftovers.erase("role");

    int res;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        res             = connection.val.write(aReq.data);
    }

    return {res};
}

crow::json::wvalue
post::UserHandler::rawDataHandler(data::RawData& aData) noexcept
{
    for (size_t i = 0; i < aData.value.size(); ++i)
    {
        if (aData.additionalInfo[i].size())
        {
            std::set<std::string> roles;
            for (auto& j : aData.additionalInfo[i])
            {
                roles.insert(j);
            }
            aData.value[i].emplace_back(
                data::wrap(core::Role::getInstance().getRoleID(roles)));
        }
    }

    return rawDataInsert<data::User>(aData.value);
}

crow::response
post::UserHandler::autorisation(const crow::request& aReq) noexcept
{
    auto x    = crow::json::load(aReq.body);
    auto resp = crow::response(400);
    if (x)
    {
        // data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
        data::User user = parseRequest<data::User>(x).data;

        std::string cond = "login = \'" + user.login + "\' AND " +
                           "password = \'" + user.password + "\'";
        {
            auto connection = data::ConnectionManager::getUserConnection();
            user            = connection.val.getData<data::User>(cond);
        }

        if (user.id)
        {
            crow::json::wvalue uJson;
            uJson["user"] = user.getAsJson({"password", "role_id"});

            auto& tokenHandler = core::TokenHandler::getInstance();
            if (tokenHandler.isActive())
                uJson["user"]["token"] = tokenHandler.generate(user);

            auto roles = core::Role::getInstance().getRoles(user.role_id);
            crow::json::wvalue::list roleList;
            for (auto& i : roles)
            {
                roleList.emplace_back(std::move(i));
            }
            uJson["user"]["role"] = std::move(roleList);

            resp = std::move(uJson);
        }
        else
        {
            resp = crow::response(401);
        }
    }
    // resp = crow::response(401);
    return resp;
}
