#include "server.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "domain/path.hpp"

#include "crow/middlewares/cors.h"

serv::Server::Server(data::DBSettings aDBS) : mDBS(aDBS)
{
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    app.loglevel(crow::LogLevel::Debug);

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

    CROW_ROUTE(app, "/api/test")
    ([]() { return "All fine!"; });

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

    CROW_ROUTE(app, "/api/drop/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, std::string aTableName)
            {
                crow::response res;
                data::DatabaseQuery dbq(mDBS);
                res = dropRequestHandler(aTableName, req, dbq);
                return res;
            });

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

    CROW_ROUTE(app, "/api/submit")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                crow::response res;

                boost::posix_time::ptime timeLocal =
                    boost::posix_time::second_clock::local_time();
                std::string dateTime;
                dateTime += std::to_string(timeLocal.date().year()) + "-";
                dateTime += std::to_string(timeLocal.date().month()) + "-";
                dateTime += std::to_string(timeLocal.date().day()) + " ";
                dateTime +=
                    std::to_string(timeLocal.time_of_day().hours()) + ":";
                dateTime +=
                    std::to_string(timeLocal.time_of_day().minutes()) + ":";
                if (timeLocal.time_of_day().seconds() < 10) dateTime += "0";
                dateTime += std::to_string(timeLocal.time_of_day().seconds());

                data::DatabaseQuery dbq(mDBS);
                data::Table<data::Submission> submition;
                submition.emplace_back();

                crow::multipart::message msg(req);
                submition.back().user_id =
                    std::stoi(msg.get_part_by_name("user_id").body);
                submition.back().problem_id =
                    std::stoi(msg.get_part_by_name("problem_id").body);

                submition.back().date_val  = dateTime;
                submition.back().verdict   = "NUN";
                submition.back().test      = -1;
                submition.back().file_path = core::PostHandler::uploadFile(
                    msg, dbq, dom::Path::getPath("submition").value());

                std::cout << dateTime << "\n";

                dbq.insert<data::Submission>(submition);

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

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/problem/<string>/<string>")
    (
        [&](std::string aProblemID, std::string aUserID)
        {
            data::DatabaseQuery dbq(mDBS);
            auto problem = dbq.getData<data::Problem>("id = " + aProblemID);
            auto submissions =
                getDataHendler("submission", "problem_id = " + aProblemID +
                                                 " AND user_id = " + aUserID);

            crow::json::wvalue result;
            result["submissions"] = std::move(submissions);

            std::string path = dom::Path::getPath("problem").value() +
                               (*((std::string*)problem[0][2])) + "/";
            std::cout << path + "data.txt\n";
            std::ifstream inp;

            inp.open(path + "data.txt");
            std::string temp, s;
            std::getline(inp, temp);
            result["name"] = temp;
            std::getline(inp, temp);
            result["time_limit"] = temp;
            std::getline(inp, temp);
            result["memory_limit"] = temp;
            int count;
            inp >> count;
            inp.close();

            inp.open(path + "legend.txt");
            temp = "";
            while (getline(inp, s))
            {
                temp += s;
            }
            result["legend"] = temp;
            inp.close();

            inp.open(path + "input_format.txt");
            temp = "";
            while (getline(inp, s))
            {
                temp += s;
            }
            result["input_format"] = temp;
            inp.close();

            inp.open(path + "output_format.txt");
            temp = "";
            while (getline(inp, s))
            {
                temp += s;
            }
            result["output_format"] = temp;
            inp.close();

            crow::json::wvalue::list examples;
            for (int i = 1; i < count + 1; ++i)
            {
                crow::json::wvalue ex;
                inp.open(path + "tests/input/" + std::to_string(i));
                std::cout << path + "tests/input/" + std::to_string(i) << "\n";
                temp = "";
                while (getline(inp, s))
                {
                    temp += s;
                }
                ex["input"] = temp;
                inp.close();

                inp.open(path + "tests/output/" + std::to_string(i));
                temp = "";
                while (getline(inp, s))
                {
                    temp += s;
                }
                ex["output"] = temp;
                inp.close();

                examples.emplace_back(std::move(ex));
            }
            result["examples"] = std::move(examples);

            crow::json::wvalue tempJson;
            tempJson["problem"] = std::move(result);

            crow::response response{tempJson};
            return response;
        });

    //--------------------------------------------------------------------------------

    // CROW_ROUTE(app, "/journal")
    // ([]() { return crow::mustache::load("index.html").render(); });
    // CROW_ROUTE(app, "/user")
    // ([]() { return crow::mustache::load("index.html").render(); });
    // CROW_ROUTE(app, "/grade")
    // ([]() { return crow::mustache::load("index.html").render(); });
    // CROW_ROUTE(app, "/plan")
    // ([]() { return crow::mustache::load("index.html").render(); });
    // CROW_ROUTE(app, "/journal_manage")
    // ([]() { return crow::mustache::load("index.html").render(); });
    // CROW_ROUTE(app, "/head_journal")
    // ([]() { return crow::mustache::load("index.html").render(); });

    //--------------------------------------------------------------------------------

    // clang-format off
    app.port(18080).multithreaded().run();
    // app.port(80).app.ssl_file("cert.crt", "keyfile.key").multithreaded().run();
    // app.port(18080).app.ssl_file("cert.crt", "keyfile.key").multithreaded().run();
    // clang-format on
}
