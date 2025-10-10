#include <format>

#include "database/include_me.hpp"

#include "kernel/framework/include_me.hpp"

#include "data_structs.hpp"

///-------

#include "user_handler.hpp"

namespace server
{

crow::response
UserHandler::autorisation(const crow::request& aReq) noexcept
{
    static auto& database = KERNEL.getModuleRef<database::DBModule>("database");
    static auto& adm_pool = database.getConnectionPool("postgres");

    auto x    = crow::json::load(aReq.body);
    auto resp = crow::response(400);
    if (x)
    {

        std::string cond = std::format("login = '{}' AND password = '{}",
                                       std::string(x["login"].s()),
                                       std::string(x["password"].s()));
        auto& connection = adm_pool.get();
        auto user_opt    = connection.select<Person>(cond);

        if (user_opt.has_value())
        {
            auto& user = user_opt.value();

            crow::json::wvalue uJson;
            uJson["user"]["id"]    = user.id;
            uJson["user"]["login"] = user.login;
            crow::json::wvalue::list roleList;
            roleList.emplace_back("add_plan");
            uJson["user"]["role"] = std::move(roleList);

            resp = std::move(uJson);
        }
        else
        {
            resp      = {"Wrong username or password!"};
            resp.code = 403;
        }
    }
    // resp = crow::response(401);
    return resp;
}

} // namespace server
