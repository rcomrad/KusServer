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
#include <map>
#include <string>
#include <unordered_map>

#include "domain/cyrillic.hpp"
#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"

int
getTime(std::string aTimeStr)
{
    std::string times = file::Parser::slice(aTimeStr, " ")[1];
    auto time         = file::Parser::slice(times, ":");
    return std::stoi(time[0]) * 60 * 60 + std::stoi(time[1]) * 60 +
           std::stoi(time[2]);
}

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

    int gloabRRR = 0;
    std::ifstream inp("login.txt");
    std::string ss;
    std::map<int, int> time;
    while (std::getline(inp, ss))
    {
        auto parts                = file::Parser::slice(ss, ";");
        time[std::stoi(parts[0])] = getTime(parts[1]) + 3 * 60 * 60;
    }

    auto users = connection.val.getDataArray<data::User>();
    for (auto& u : users)
    {
        auto answer = connection.val.getDataArray<data::Answer>(
            "user_id=" + data::wrap(u.id));
        int mimTime = 1e9;
        int userId  = 0;
        for (auto& a : answer)
        {
            int curTime = getTime(a.time);
            mimTime     = std::min(mimTime, curTime);
            userId      = a.userID;
        }
        // if (!time.count(userId))
        {
            time[userId] = mimTime - (rand() % 600 + 300);
            gloabRRR++;
        }
    }
    // std::cout << gloabRRR << "\n";
    // std::cin >> gloabRRR;

    std::string res6;
    std::string res7;
    std::string res8;
    for (auto& u : users)
    {
        int sum      = 0;
        int abs_sum  = 0;
        int time_sum = 0;
        std::string res;
        std::vector<int> aa(6);
        auto answer = connection.val.getDataArray<data::Answer>(
            "user_id=" + data::wrap(u.id));
        if (u.login == "6ACT100")
        {
            int yy = 0;
            ++yy;
        }
        for (auto& a : answer)
        {
            int num = (a.questionID - 1) % 6;
            // int answerTime = getTime(a.time) - time[a.userID];
            // if (time.count(a.userID) && answerTime > 3600)
            // {
            //     aa[num] = -1000;
            // }
            // else if (!time.count(a.userID))
            // {
            //     aa[num] = -100000000;
            // }
            // else
            // {
            aa[num] = a.verdict == "T" ? 2 : -2;
            if (num == 0 || num == 2) aa[num] /= 2;
            if (num == 1 && a.verdict == "F")
            {
                auto parts = file::Parser::slice(a.value, " ");
                if (parts.size() == 2)
                {
                    if (a.questionID == 2 && parts.size() == 2 &&
                        (parts[0] == "6" || parts[1] == "3"))
                    {
                        aa[num] = 1;
                    }
                    if (a.questionID == 8 && parts.size() == 2 &&
                        (parts[0] == "7" || parts[1] == "4"))
                        aa[num] = 1;
                    if (a.questionID == 14 && parts.size() == 2 &&
                        (parts[0] == "11" || parts[1] == "6"))
                        aa[num] = 1;
                }
            }

            if (num == 3 && a.verdict == "F")
            {
                auto parts = file::Parser::slice(a.value, " ");
                if (parts.size() == 3)
                {
                    std::string frst  = parts[0] + parts[1];
                    std::string secnd = parts[2];
                    auto question     = connection.val.getData<data::Question>(
                        "id=" + data::wrap(a.questionID));

                    parts = file::Parser::slice(question.juryAnswer, " ");
                    std::string aF = parts[0] + parts[1];
                    std::string aS = parts[2];

                    if (frst == aF)
                    {
                        aa[num] = 1;
                    }
                    if (secnd == aS)
                    {
                        aa[num] = 1;
                    }
                }

                if (aa[num] == -1)
                {
                    int tt = 0;
                    ++tt;
                }
            }
            // }

            sum += aa[num] > 0 ? aa[num] : 0;
            abs_sum += std::abs(aa[num]) ? 1 : 0;

            // if (answerTime < 0)
            // {
            //     int yy = 0;
            //     yy++;
            // }
            // if (aa[num] > 0)
            // {
            //     aa[num] = answerTime;
            //     time_sum += aa[num];
            // }
            // else
            // {
            //     aa[num] = -answerTime;
            // }
        }

        res += u.login;
        for (auto& a : aa)
        {
            res += ";";
            res += std::to_string(a);
        }
        res += ";" + std::to_string(sum) + ";" + std::to_string(abs_sum);
        res += "\n";

        if (res[0] == '6')
        {
            res6 += res;
        }
        if (res[0] == '7')
        {
            res7 += res;
        }
        if (res[0] == '8')
        {
            res8 += res;
        }
    }
    std::ofstream out("out.txt");
    out << res6 << "\n" << res7 << "\n" << res8;
    std::ofstream out6("out6.txt");
    out6 << res6;
    std::ofstream out7("out7.txt");
    out7 << res7;
    std::ofstream out8("out8.txt");
    out8 << res8;
    return "";
}

std::string
supRes()
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

    std::string res;
    auto users = connection.val.getDataArray<data::User>();
    for (auto& u : users)
    {
        std::vector<int> line(5);
        auto submission = connection.val.getDataArray<data::Submission>(
            "user_id=" + data::wrap(u.id));

        bool flag = true;

        if (u.login == "8KRSNS201006")
        {
            int yy = 0;
            ++yy;
        }

        int points = 0, penalty = 0;
        for (auto& s : submission)
        {
            flag     = false;
            int p_id = s.problemID - 1;
            if (s.verdict == "CE" || line[p_id] > 0) continue;
            if (line[p_id] > 0) continue;
            --line[p_id];
            if (s.verdict == "OK")
            {
                int yy1 = getTime(s.dateVal);
                int yy2 = getTime("1 10:00:00");
                int yy3 = yy1 - yy2;

                line[p_id] *= -1;
                ++points;
                penalty += (line[p_id] - 1) * 20 * 60;
                penalty += yy3;
            }
        }

        line.emplace_back(points);
        line.emplace_back(penalty);

        if (flag) continue;

        res += u.login;
        for (auto& i : line)
        {
            res += ";";
            res += std::to_string(i);
        }
        res += "\n";
    }
    std::ofstream out("out.txt");
    out << res;
    return "";
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

    CROW_ROUTE(mApp, "/api/www")
    ([]() { return supRes(); });

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
