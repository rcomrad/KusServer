#include "server.hpp"

#include "core/file_router.hpp"
#include "core/variable_storage.hpp"
#include "crow/middlewares/cors.h"
#include "file_data/parser.hpp"
#include "get/competition_handler.hpp"
#include "get/get_handler.hpp"
#include "get/get_router.hpp"
#include "get/problem_handler.hpp"
#include "get/question_handler.hpp"
#include "multitool/command_handler.hpp"
#include "multitool/dump_manager.hpp"
#include "multitool/multitool_router.hpp"
#include "post/post_router.hpp"
#include "post/print_journal.hpp"
#include "post/submit_handler.hpp"
#include "post/user_handler.hpp"
crow::App<crow::CORSHandler, serv::Middleware> serv::Server::mApp;

#include <fstream>
#include <string>
#include <unordered_map>

#include "domain/cyrillic.hpp"
#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
std::string
susRes()
{
    auto connection = data::ConnectionManager::getUserConnection();

    // auto questionIDs =
    // connection.val.getDataArray<data::CompetitionQuestion>(
    //     "competition_id=" + data::wrap(aCompetitionID));
    //     std::string cond;
    //     for(auto& i : questionIDs) cond += "id=" +
    //     std::to_string(i.questionID) + " OR "; cond.resize(cond.size() - 4);
    //     auto questions = connection.val.getDataArray<data::Question>(
    //     cond);

    auto users = connection.val.getDataArray<data::User>();
    std::string res;
    for (auto& u : users)
    {
        std::vector<int> aa(6);
        auto answer = connection.val.getDataArray<data::Answer>(
            "user_id=" + data::wrap(u.id));
        for (auto& a : answer)
        {
            int num = a.questionID % 6;

            std::string times = file::Parser::slice(a.time, " ")[1];
            auto time         = file::Parser::slice(times, ":");
            aa[num] = std::stoi(time[0]) * 60 * 60 + std::stoi(time[1]) * 60 +
                      std::stoi(time[2]);
            aa[num] *= a.verdict == "T" ? 1 : -1;
        }

        res += u.login;
        for (auto& a : aa)
        {
            res += " ";
            res += std::to_string(a);
        }
        res += "\n";
    }
    return res;
}

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
    ([](const std::string& aType, const std::string& aValue)
     { return mult::CommandHandler::process(aType, aValue); });

    // CROW_ROUTE(mApp, "/api/multitool/<string>")
    //     .methods("POST"_method)(
    //         [&](const crow::request& req, const std::string& aArg)
    //         {
    //             crow::response res;
    //             res = post::PostHandler::uploadFromFileRequest(aType, req);
    //             return res;
    //         });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/print_journal/<string>")
    ([](const std::string& aIDs) { return post::PrintJournal::process(aIDs); });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/get/all/<string>")
    ([&](const std::string& aRequest)
     { return get::GetHandler::multiplelGet(aRequest, ""); });

    CROW_ROUTE(mApp, "/api/get/by_id/<string>/<string>")
    ([&](const std::string& aRequest, const std::string& aID)
     { return get::GetHandler::singlGet(aRequest, "id = " + aID); });

    CROW_ROUTE(mApp, "/api/get/if/<string>/<string>")
    ([&](const std::string& aRequest, std::string aCondition)
     { return get::GetHandler::multiplelGet(aRequest, aCondition); });

    CROW_ROUTE(mApp, "/api/dump/<string>")
    ([&](const std::string& aName)
     { return mult::CommandHandler::process("dump", aName); });
    CROW_ROUTE(mApp, "/api/dump_as_file/<string>")
    ([&](const std::string& aName)
     { return mult::CommandHandler::process("dump_as_file", aName); });

    CROW_ROUTE(mApp, "/api/get_all_competition/<int>/<int>")
    ([&](int aUserID, int aCompetitionID)
     { return get::CompetitionHandler::process(aUserID, aCompetitionID); });

    CROW_ROUTE(mApp, "/api/get_question/<int>/<int>")
    ([&](int aQuestionID, int aUserID)
     { return get::QuestionHandler::process(aQuestionID, aUserID); });

    CROW_ROUTE(mApp, "/api/qqq")
    ([]() { return susRes(); });

    CROW_ROUTE(mApp, "/api/get_problem/<int>/<int>")
    ([&](int aProblemID, int aUserID)
     { return get::ProblemHandler::process(aProblemID, aUserID); });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/drop/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const std::string& aTableName)
            {
                crow::response res;
                res = post::PostRouter::dropRouter(aTableName, req);
                return res;
            });

    //---------------------------------------------------------------------

    CROW_ROUTE(mApp, "/api/post/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const std::string& aTableName)
            {
                crow::response res;
                res = post::PostRouter::processRouter(aTableName, req);
                return res;
            });

    CROW_ROUTE(mApp, "/api/upload/<string>")
        .methods("POST"_method)(
            [&](const crow::request& req, const std::string& aType)
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
    ([&](const std::string& aUrl)
     { return post::UserHandler::confirmation(aUrl); });

    mApp.port(18080).multithreaded().run();
}

const serv::Middleware::context&
serv::Server::getContext(const crow::request& aReq) noexcept
{
    return mApp.get_context<Middleware>(aReq);
}
