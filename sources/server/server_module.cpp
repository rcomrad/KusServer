// #include "database/include_me.hpp"

#include "kernel/framework/include_me.hpp"

//-----------

#include "server_module.hpp"
#include "user_handler.hpp"

namespace server
{

auto module_name = "server";
REG_MODULE(module_name, ServerModule);

ServerModule::ServerModule() : core::Module(module_name)
{
}

void
ServerModule::initialize()
{
    // crow::App<TokenHandler> mApp;
    auto& cors = mApp.get_middleware<crow::CORSHandler>();
    mApp.loglevel(crow::LogLevel::Debug);

    // clang-format off
    cors
      .global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
        .methods("POST"_method, "GET"_method)
        .origin("*")
      .prefix("/")
        .ignore();
    // clang-format on

    // auto& database = KERNEL.getModuleRef<database::DBModule>("database");
    // auto& adm_pool = database.getConnectionPool("postgres");
    // auto& adm_conn = adm_pool.get();

    CROW_ROUTE(mApp, "/api/yahoo")
        .methods("POST"_method)([&](const crow::request& req)
                                { return "yahoo"; });

    CROW_ROUTE(mApp, "/api/login")
        .methods("POST"_method)([&](const crow::request& req)
                                { return UserHandler::autorisation(req); });

    mApp.port(18080).multithreaded().run();
}

} // namespace server
