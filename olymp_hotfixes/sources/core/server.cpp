#include "server.hpp"

#include "crow/middlewares/cors.h"
#include "file/file_router.hpp"
#include "get/command_handler.hpp"
#include "get/competition_handler.hpp"
#include "get/get_handler.hpp"
#include "get/get_router.hpp"
#include "get/problem_handler.hpp"
#include "get/question_handler.hpp"
#include "post/post_router.hpp"
#include "post/submit_handler.hpp"
#include "post/user_handler.hpp"

#include "result_generator.hpp"
#include "token_handler.hpp"

void
core::TokenMiddleware::before_handle(crow::request& req,
                                     crow::response& res,
                                     context& ctx)
{
    // if (req.remote_ip_address != ADMIN_IP)
    // {
    //     res.code = 403;
    //     res.end();
    // }
    // std::cout << req.raw_url << "\n";
    auto& handler = core::TokenHandler::getInstance();
    if (req.headers.find("token") != req.headers.end())
    {
        auto token = req.get_header_value("token");
        if (handler.check(token, req.raw_url))
        {
            res.code = 403;
            res.end();
        }
    }
    else
    {
        if (req.raw_url != "/api/login" && handler.isActive())
        {
            res.code = 403;
            res.end();
        }
    }
}

void
core::TokenMiddleware::after_handle(crow::request& req,
                                    crow::response& res,
                                    context& ctx)
{
}

core::Server::Server()
{
    crow::App<crow::CORSHandler, TokenMiddleware> app;
    // crow::App<TokenHandler> app;
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

    CROW_ROUTE(app, "/api/exload")
    (
        []()
        {
            file::FileRouter::process("exload.dmp");

            return "5";
        });

    CROW_ROUTE(app, "/api/get_results/<int>")
    (
        [](int aCompetitionID)
        {
            core::ResultGenerator::generate(aCompetitionID);
            return "4";
        });

    CROW_ROUTE(app, "/api/command/<string>/<string>")
    ([](std::string aType, std::string aValue)
     { return get::CommandHandler::process(aType, aValue); });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/get/all/<string>")
    ([&](std::string aRequest)
     { return get::GetHandler::multiplelGet(aRequest, ""); });

    CROW_ROUTE(app, "/api/get/by_id/<string>/<string>")
    ([&](std::string aRequest, std::string aID)
     { return get::GetHandler::singlGet(aRequest, "id = " + aID); });

    CROW_ROUTE(app, "/api/get/if/<string>/<string>")
    (
        [&](std::string aRequest, std::string aCondition) {
            return get::GetHandler::multiplelGet(aRequest,
                                                 std::move(aCondition));
        });

    CROW_ROUTE(app, "/api/dump/<string>")
    ([&](std::string aName) { return get::GetRouter::dumpRouter(aName); });

    CROW_ROUTE(app, "/api/get_all_competition/<int>/<int>")
    ([&](int aUserID, int aCompetitionID)
     { return get::CompetitionHandler::process(aUserID, aCompetitionID); });

    CROW_ROUTE(app, "/api/get_question/<int>/<int>")
    ([&](int aQuestionID, int aUserID)
     { return get::QuestionHandler::process(aQuestionID, aUserID); });

    CROW_ROUTE(app, "/api/get_problem/<int>/<int>")
    ([&](int aProblemID, int aUserID)
     { return get::ProblemHandler::getProblem(aProblemID, aUserID); });

    //---------------------------------------------------------------------

    // CROW_ROUTE(app, "/api/get_question/<string>/<string>")
    // ([&](std::string aRequest, std::string aUserID)
    //  { return get("question", std::move(aRequest), aUserID); });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/drop/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, std::string aTableName)
            {
                crow::response res;
                res = post::PostRouter::dropRouter(aTableName, req);
                return res;
            });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/post/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, std::string aTableName)
            {
                crow::response res;
                res = post::PostRouter::basicRouter(aTableName, req);
                return res;
            });

    CROW_ROUTE(app, "/api/upload/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, std::string aTableName)
            {
                crow::response res;
                res = post::PostRouter::uploadRouter(aTableName, req);
                return res;
            });

    CROW_ROUTE(app, "/api/submit")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                crow::response res;
                res = post::SubmitHandler::process(req);
                return res;
            });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/login")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                crow::response res;
                res = post::UserHandler::autorisation(req);
                return res;
            });

    //---------------------------------------------------------------------

    // CROW_ROUTE(app, "/api/problem/<string>/<string>")
    // (
    //     [&](std::string aProblemID, std::string aUserID)
    //     {
    //         data::DatabaseQuery dbq(mDBS);
    //         auto problem = dbq.getData<data::Problem>("id = " + aProblemID);
    //         auto submissions =
    //             getDataHendler("submission", "problem_id = " + aProblemID +
    //                                              " AND user_id = " +
    //                                              aUserID);

    //         crow::json::wvalue result;
    //         result["submissions"] = std::move(submissions);

    //         std::string path = dom::Path::getPath("problem").value() +
    //                            (*((std::string*)problem[0][2])) + "/";
    //         std::cout << path + "data.txt\n";
    //         std::ifstream inp;

    //         inp.open(path + "data.txt");
    //         std::string temp, s;
    //         std::getline(inp, temp);
    //         result["name"] = temp;
    //         std::getline(inp, temp);
    //         result["time_limit"] = temp;
    //         std::getline(inp, temp);
    //         result["memory_limit"] = temp;
    //         int count;
    //         inp >> count;
    //         inp.close();

    //         inp.open(path + "legend.txt");
    //         temp = "";
    //         while (getline(inp, s))
    //         {
    //             temp += s;
    //         }
    //         result["legend"] = temp;
    //         inp.close();

    //         inp.open(path + "input_format.txt");
    //         temp = "";
    //         while (getline(inp, s))
    //         {
    //             temp += s;
    //         }
    //         result["input_format"] = temp;
    //         inp.close();

    //         inp.open(path + "output_format.txt");
    //         temp = "";
    //         while (getline(inp, s))
    //         {
    //             temp += s;
    //         }
    //         result["output_format"] = temp;
    //         inp.close();

    //         crow::json::wvalue::list examples;
    //         for (int i = 1; i < count + 1; ++i)
    //         {
    //             crow::json::wvalue ex;
    //             inp.open(path + "tests/input/" + std::to_string(i));
    //             std::cout << path + "tests/input/" + std::to_string(i) <<
    //             "\n"; temp = ""; while (getline(inp, s))
    //             {
    //                 temp += s;
    //             }
    //             ex["input"] = temp;
    //             inp.close();

    //             inp.open(path + "tests/output/" + std::to_string(i));
    //             temp = "";
    //             while (getline(inp, s))
    //             {
    //                 temp += s;
    //             }
    //             ex["output"] = temp;
    //             inp.close();

    //             examples.emplace_back(std::move(ex));
    //         }
    //         result["examples"] = std::move(examples);

    //         crow::json::wvalue tempJson;
    //         tempJson["problem"] = std::move(result);

    //         crow::response response{tempJson};
    //         return response;
    //     });

    app.port(18080).multithreaded().run();
}
