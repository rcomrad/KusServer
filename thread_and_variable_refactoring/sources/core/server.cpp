#include "server.hpp"

#include "core/file_router.hpp"
#include "crow/middlewares/cors.h"
#include "file_data/parser.hpp"
#include "get/competition_handler.hpp"
#include "get/get_handler.hpp"
#include "get/get_router.hpp"
#include "get/question_handler.hpp"
#include "multitool/command_handler.hpp"
#include "multitool/dump_manager.hpp"
#include "multitool/multitool_router.hpp"
#include "post/post_router.hpp"
#include "post/print_journal.hpp"
#include "post/submit_handler.hpp"
#include "post/user_handler.hpp"

#include "result_generator.hpp"
#include "token_handler.hpp"

void
core::TokenMiddleware::before_handle(crow::request& req,
                                     crow::response& res,
                                     context& ctx)
{
    static auto& handler = core::TokenHandler::getInstance();
    if (!handler.process(req))
    {
        res.code = 403;
        res.end();
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
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
        .methods("POST"_method, "GET"_method)
        .origin("*")
      .prefix("/")
        .ignore();
    // clang-format on

    //--------------------------------------------------------

    CROW_ROUTE(app, "/api/test")
    ([]() { return "All fine!"; });

    CROW_ROUTE(app, "/api/exload")
    (
        []()
        {
            post::PostHandler::uploadFromFile(
                {
                    {"type", "nun"}
            },
                "exload.dmp");

            return "Exfinished";
        });

    CROW_ROUTE(app, "/api/get_results/<int>")
    (
        [](int aCompetitionID)
        {
            core::ResultGenerator::generate(aCompetitionID);
            return "4";
        });

    CROW_ROUTE(app, "/api/command/<string>/<string>")
    ([](const std::string& aType, const std::string& aValue)
     { return mult::CommandHandler::process(aType, aValue); });

    // CROW_ROUTE(app, "/api/multitool/<string>")
    //     .methods("POST"_method)(
    //         [&](const crow::request& req, const std::string& aArg)
    //         {
    //             crow::response res;
    //             res = post::PostHandler::uploadFromFileRequest(aType, req);
    //             return res;
    //         });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/print_journal/<string>")
    ([](const std::string& aIDs) { return post::PrintJournal::process(aIDs); });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/get/all/<string>")
    ([&](const std::string& aRequest)
     { return get::GetHandler::multiplelGet(aRequest, ""); });

    CROW_ROUTE(app, "/api/get/by_id/<string>/<string>")
    ([&](const std::string& aRequest, const std::string& aID)
     { return get::GetHandler::singlGet(aRequest, "id = " + aID); });

    CROW_ROUTE(app, "/api/get/if/<string>/<string>")
    ([&](const std::string& aRequest, std::string aCondition)
     { return get::GetHandler::multiplelGet(aRequest, aCondition); });

    CROW_ROUTE(app, "/api/dump/<string>")
    ([&](const std::string& aName)
     { return mult::CommandHandler::process("dump", aName); });
    CROW_ROUTE(app, "/api/dump_as_file/<string>")
    ([&](const std::string& aName)
     { return mult::CommandHandler::process("dump_as_file", aName); });

    CROW_ROUTE(app, "/api/get_all_competition/<int>/<int>")
    ([&](int aUserID, int aCompetitionID)
     { return get::CompetitionHandler::process(aUserID, aCompetitionID); });

    CROW_ROUTE(app, "/api/get_question/<int>/<int>")
    ([&](int aQuestionID, int aUserID)
     { return get::QuestionHandler::process(aQuestionID, aUserID); });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/drop/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const std::string& aTableName)
            {
                crow::response res;
                res = post::PostRouter::dropRouter(aTableName, req);
                return res;
            });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/post/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const std::string& aTableName)
            {
                crow::response res;
                res = post::PostRouter::processRouter(aTableName, req);
                return res;
            });

    CROW_ROUTE(app, "/api/upload/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const std::string& aType)
            {
                crow::response res;
                res = post::PostHandler::uploadFromFileRequest(aType, req);
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

    CROW_ROUTE(app, "/api/multitool")
        .methods("POST"_method)([&](const crow::request& req)
                                { return mult::MultitoolRouter::route(req); });

    //---------------------------------------------------------------------

    CROW_ROUTE(app, "/api/login")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                crow::response res;
                res = post::UserHandler::autorisation(req);
                return res;
            });

    CROW_ROUTE(app, "/api/registration")
        .methods("POST"_method)(
            [&](const crow::request& req)
            { return post::UserHandler::registration(req); });

    CROW_ROUTE(app, "/api/confirm/<string>")
    ([&](const std::string& aUrl)
     { return post::UserHandler::confirmation(aUrl); });

    app.port(18080).multithreaded().run();
}
