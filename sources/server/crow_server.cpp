#include "crow_server.hpp"

crow::App<crow::CORSHandler> serv::CROWServer::mApp;

serv::CROWServer::CROWServer()
{
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

    //--------------------------------------------------------

    initializeRouts();

    mApp.port(18080).multithreaded().run();
}

void
serv::CROWServer::initializeRouts()
{
    CROW_ROUTE(mApp, "/api/test")
    ([]() { return "All fine!"; });
}
