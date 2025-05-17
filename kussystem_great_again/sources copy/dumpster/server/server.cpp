#include "server.hpp"

#include "core/file_router.hpp"
#include "core/variable_storage.hpp"

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

crow::App<crow::CORSHandler, serv::Middleware> serv::Server::mApp;

serv::Server::Server() noexcept
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

    //--------------------------------------------------------

    CROW_ROUTE(mApp, "/api/test")
    ([]() { return "All fine!"; });

    CROW_ROUTE(mApp, "/api/exload")
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

    // CROW_ROUTE(mApp, "/api/get_results/<int>")
    // (
    //     [&mApp](int aCompetitionID)
    //     {
    //         core::ResultGenerator::generate(aCompetitionID);
    //         return "4";
    //     });

    CROW_ROUTE(mApp, "/api/command/<string>/<string>")
    ([](const char* aType, const char* aValue)
     { return mult::CommandHandler::process(aType, aValue); });

    // CROW_ROUTE(mApp, "/api/multitool/<string>")
    //     .methods("POST"_method)(
    //         [&](const crow::request& req, const char* aArg)
    //         {
    //             crow::response res;
    //             res = post::PostHandler::uploadFromFileRequest(aType, req);
    //             return res;
    //         });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/print_journal/<string>")
    ([](const char* aIDs) { return post::PrintJournal::process(aIDs); });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/get/all/<string>")
    ([&](const char* aRequest)
     { return get::GetHandler::multiplelGet(aRequest, ""); });

    CROW_ROUTE(mApp, "/api/get/by_id/<string>/<string>")
    ([&](const char* aRequest, const char* aID)
     { return get::GetHandler::singlGet(aRequest, "id = " + aID); });

    CROW_ROUTE(mApp, "/api/get/if/<string>/<string>")
    ([&](const char* aRequest, str::String aCondition)
     { return get::GetHandler::multiplelGet(aRequest, aCondition); });

    CROW_ROUTE(mApp, "/api/dump/<string>")
    ([&](const char* aName)
     { return mult::CommandHandler::process("dump", aName); });
    CROW_ROUTE(mApp, "/api/dump_as_file/<string>")
    ([&](const char* aName)
     { return mult::CommandHandler::process("dump_as_file", aName); });

    CROW_ROUTE(mApp, "/api/get_all_competition/<int>/<int>")
    ([&](int aUserID, int aCompetitionID)
     { return get::CompetitionHandler::process(aUserID, aCompetitionID); });

    CROW_ROUTE(mApp, "/api/get_question/<int>/<int>")
    ([&](int aQuestionID, int aUserID)
     { return get::QuestionHandler::process(aQuestionID, aUserID); });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/drop/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const char* aTableName)
            {
                crow::response res;
                res = post::PostRouter::dropRouter(aTableName, req);
                return res;
            });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/post/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const char* aTableName)
            {
                crow::response res;
                res = post::PostRouter::processRouter(aTableName, req);
                return res;
            });

    CROW_ROUTE(mApp, "/api/upload/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const char* aType)
            {
                crow::response res;
                res = post::PostHandler::uploadFromFileRequest(aType, req);
                return res;
            });

    CROW_ROUTE(mApp, "/api/submit")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                crow::response res;
                res = post::SubmitHandler::process(req);
                return res;
            });

    CROW_ROUTE(mApp, "/api/multitool")
        .methods("POST"_method)([&](const crow::request& req)
                                { return mult::MultitoolRouter::route(req); });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/login")
        .methods("POST"_method)(
            [&](const crow::request& req)
            {
                crow::response res;
                res = post::UserHandler::autorisation(req);
                return res;
            });

    CROW_ROUTE(mApp, "/api/registration")
        .methods("POST"_method)(
            [&](const crow::request& req)
            { return post::UserHandler::registration(req); });

    CROW_ROUTE(mApp, "/api/confirm/<string>")
    ([&](const char* aUrl) { return post::UserHandler::confirmation(aUrl); });

    mApp.port(18080).multithreaded().run();
}

const serv::Middleware::context&
serv::Server::getContext(const crow::request& aReq) noexcept
{
    return mApp.get_context<Middleware>(aReq);
}
