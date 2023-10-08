#include "command_handler.hpp"

#include "domain/url_wrapper.hpp"

#include "database/connection_manager.hpp"

#include "core/core.hpp"
#include "core/token_handler.hpp"
#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "file_data/variable_storage.hpp"

#include "crow_helper.hpp"
#include "dump_manager.hpp"

std::unordered_map<std::string, decltype(&mult::CommandHandler::restart)>
    mult::CommandHandler::mRouterMap = {
        {"restart",  &mult::CommandHandler::restart     },
        {"token",    &mult::CommandHandler::tokenHandler},
        {"kill",     &mult::CommandHandler::kill        },
        {"question", &mult::CommandHandler::question    },
        {"results",  &mult::CommandHandler::results     },
 // {"check",   &mult::CommandHandler::check  },
  // {"time",    &mult::CommandHandler::time   }
};

std::string
mult::CommandHandler::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    auto command = CrowHelper::getPart(msg, "command");
    auto value   = CrowHelper::getPart(msg, "value");

    return process(command, value);
}

std::string
mult::CommandHandler::process(const std::string& aType,
                              const std::string& aValue) noexcept
{
    std::string res = "ERROR\nInvalid command!\n>:(\n";
    auto it         = mRouterMap.find(aType);
    if (it != mRouterMap.end()) res = it->second(aValue);
    return res;
}

std::string
mult::CommandHandler::restart(const std::string aValue) noexcept
{
    std::string res = "ERROR\nNo restart :( \nInvalid restart value.";
    int resValue    = 0;
    auto& state     = file::VariableStorage::getInstance();

    if (aValue == "full")
    {
        resValue = 7;
        res      = "OK\nFull restart!";
    }
    else if (aValue == "empty")
    {
        resValue = 1;
        res      = "OK\nEmpty restart!";
    }
    else if (aValue == "tester")
    {
        resValue = 4;
        res      = "OK\nTester restart!";
    }

    if (resValue)
    {
        auto dumpPath = mult::DumpManager::makeSaveFile();
        if (dumpPath.has_value())
        {
            res += "\n\nDump address: " + dumpPath.value();
            state.setVariable("restart", resValue);
        }
        else
        {
            res = "ERROR\nCan't create dump!";
        }
    }

    while (state.getIntUnsafe("restart"))
        ;

    return res;
}

std::string
mult::CommandHandler::tokenHandler(const std::string aValue) noexcept
{
    std::string res = "ERROR\nWrong token command.";
    if (core::TokenHandler::getInstance().executeCommand(aValue))
    {
        res = "Token command applyed.";
    }

    return res;
}

std::string
mult::CommandHandler::kill(const std::string aValue) noexcept
{
    core::Core::getInstance().kill();
    return "";
}

std::string
mult::CommandHandler::question(const std::string aValue) noexcept
{
    std::string result = "ERROR: no such command!";
    if (aValue == "load")
    {
        result = loadQuestions();
    }
    else if (aValue == "retest")
    {
        result = retestQuestions();
    }
    return result;
}

std::string
mult::CommandHandler::loadQuestions() noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    // connection.val.drop("question", "id > 0");

    auto hasQ = file::Path::getContentMap(file::Path::getPathUnsafe("question"),
                                          file::Path::FileType::Folder);
    std::map<std::string, std::string> q;
    q.insert(hasQ.begin(), hasQ.end());

    auto ans = file::File::getWordsMap("question"s, "ans.txt"s);

    for (auto& i : q)
    {
        data::Question q = connection.val.getData<data::Question>(
            "nickname=\'" + i.first + "\'");

        q.name       = i.first;
        q.nickname   = i.first;
        q.type       = "simpl";
        q.weight     = 1;
        q.juryAnswer = "1";

        auto it = ans.find(i.first);
        if (it != ans.end())
        {
            q.juryAnswer = it->second;
            q.juryAnswer.push_back('.');
        }

        connection.val.write(q);
    }

    return "?";
}

std::string
mult::CommandHandler::retestQuestions() noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    auto temp       = connection.val.getDataArray<data::Question>();
    std::unordered_map<int, data::Question> questions;
    for (auto&& i : temp)
    {
        questions[i.id] = std::move(i);
    }

    auto answers = connection.val.getDataArray<data::Answer>();
    for (auto& a : answers)
    {
        a.verdict = (a.value == questions[a.questionID].juryAnswer) ? "T" : "F";
    }

    connection.val.write(answers);

    return "?";
}

std::string
mult::CommandHandler::results(const std::string aValue) noexcept
{
    std::string results;

    auto connection   = data::ConnectionManager::getUserConnection();
    auto com_question = connection.val.getDataArray<data::CompetitionQuestion>(
        "competition_id = " + aValue);
    std::vector<data::Question> questions;
    for (auto& i : com_question)
    {
        questions.emplace_back(connection.val.getData<data::Question>(
            "id = " + data::wrap(i.questionID)));
    }

    auto users = connection.val.getDataArray<data::User>();

    for (auto& u : users)
    {
        results += u.login + " ; ";
        for (auto& q : questions)
        {
            auto answer = connection.val.getData<data::Answer>(
                "user_id = " + data::wrap(u.id) +
                " AND "
                "question_id = " +
                data::wrap(q.id));
            if (answer.id)
            {
                results += answer.verdict + ";";
            }
            else
            {
                results += " ;";
            }
        }
        results += "\n";
    }

    file::File::writeData("print", "results.txt", results);

    return dom::UrlWrapper::toSite("print/results.txt");
}
