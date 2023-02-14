#include "server.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "crow/middlewares/cors.h"

serv::Server::Server(data::DBSettings aDBS) : mDBS(aDBS)
{
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    app.loglevel(crow::LogLevel::Debug);

#ifdef CROW_ENABLE_SSL

    app.ssl_file("cert.crt", "keyfile.key");

#endif

    // clang-format off
    cors
      .global()
        .headers("*")
        .methods("POST"_method, "GET"_method)
        .origin("*")
      .prefix("/cors")
        .origin("*")
        .headers("*")
        .methods("POST"_method, "GET"_method)
        .origin("*")
      .prefix("/nocors")
        .ignore();
    // clang-format on

    //--------------------------------------------------------
    CROW_ROUTE(app, "/")
    ([]() { return crow::mustache::load("index.html").render(); });

    CROW_ROUTE(app, "/test")
    ([]() { return "All fine!"; });

    CROW_ROUTE(app, "/favicon.ico")
    (
        [](const crow::request&, crow::response& res)
        {
            res.set_static_file_info("assets/favicon.ico");
            res.end();
        });
    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/get/all/<string>")
    ([&](std::string aRequest) { return get(aRequest, ""); });

    CROW_ROUTE(app, "/api/get/by_id/<string>/<string>")
    ([&](std::string aRequest, std::string aID)
     { return get(aRequest, "id = " + aID); });

    CROW_ROUTE(app, "/api/get/if/<string>/<string>")
    ([&](std::string aRequest, std::string aCondition)
     { return get(aRequest, std::move(aCondition)); });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/post/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, std::string aTableName)
            {
                crow::response res;
                data::DatabaseQuery dbq(mDBS);
                res = postRequestHandler(aTableName, req, dbq);
                return res;
            });

    CROW_ROUTE(app, "/api/upload/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, std::string aTableName)
            {
                crow::response res;
                if (aTableName == "plan")
                {
                    data::DatabaseQuery dbq(mDBS);
                    core::PlanHandler::loadFromRequest(req, dbq);
                    // res = PlanHandler::loadFromRequest(req, dbq);
                }
                return res;
            });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/login")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                auto x    = crow::json::load(req.body);
                auto resp = crow::response(400);
                if (x)
                {
                    data::DatabaseQuery dbq(mDBS);
                    auto user =
                        core::PostHandler::getStructTable<data::User>(x, dbq);
                    std::string cond = "login = \'" + user[0].login +
                                       "\' AND " + "password = \'" +
                                       user[0].password + "\'";
                    resp = get("user", std::move(cond));
                }
                return resp;
            });

    //--------------------------------------------------------------------------------

    CROW_ROUTE(app, "/journal")
    ([]() { return crow::mustache::load("index.html").render(); });
    CROW_ROUTE(app, "/user")
    ([]() { return crow::mustache::load("index.html").render(); });
    CROW_ROUTE(app, "/grade")
    ([]() { return crow::mustache::load("index.html").render(); });
    CROW_ROUTE(app, "/plan")
    ([]() { return crow::mustache::load("index.html").render(); });
    CROW_ROUTE(app, "/journal_manage")
    ([]() { return crow::mustache::load("index.html").render(); });
    CROW_ROUTE(app, "/head_journal")
    ([]() { return crow::mustache::load("index.html").render(); });

    //--------------------------------------------------------------------------------

    // clang-format off
    app.port(80).multithreaded().run();
    // app.port(80).app.ssl_file("cert.crt", "keyfile.key").multithreaded().run();
    // app.port(18080).app.ssl_file("cert.crt", "keyfile.key").multithreaded().run();
    // clang-format on
}
