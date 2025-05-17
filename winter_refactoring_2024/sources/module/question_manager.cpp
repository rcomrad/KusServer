#include "question_manager.hpp"

#include <algorithm>

#include "database/connection_manager.hpp"

#include "domain/variable_storage.hpp"

#include "text_data/file.hpp"
#include "text_data/parser.hpp"
#include "text_data/path.hpp"

mod::QuestionManager mod::QuestionManager::mInstance;

mod::QuestionManager::QuestionManager() noexcept : ModuleBase({"question"})
{
}

std::string
mod::QuestionManager::doAction(const Command& aComman) noexcept
{
    std::string result = "LOG_ERROR: no such command!";
    if (aComman.argument == "load")
    {
        result = loadQuestions();
    }
    else if (aComman.argument == "retest")
    {
        result = retestQuestions();
    }
    return result;
}

std::string
mod::QuestionManager::loadQuestions() noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    // connection.val.drop("question", "id > 0");

    auto hasQ = text::Path::getContentMap(text::Path::getPathUnsafe("question"),
                                          text::Path::FileType::Folder);
    std::map<std::string, std::string> questions;
    questions.insert(hasQ.begin(), hasQ.end());

    for (auto& i : questions)
    {
        data::Question q = connection.val.getData<data::Question>(
            "nickname=\'" + i.first + "\'");

        q.name       = i.first;
        q.nickname   = i.first;
        q.type       = "simpl";
        q.weight     = 1;
        q.juryAnswer = "1";

        auto data = text::File::getWordsMap(
            i.second + "data.txt", text::FileType::File,
            [](char c) { return c == '=' || c == '\n' || c == '\0'; });

        auto ansIt  = data.find("answer");
        auto typeIt = data.find("type");
        auto nameIt = data.find("name");

        if (ansIt != data.end()) q.juryAnswer = ansIt->second;
        if (typeIt != data.end()) q.type = typeIt->second;
        if (nameIt != data.end()) q.name = nameIt->second;

        connection.val.write(q);
    }

    return "?";
}
#include "text_data/cyrillic.hpp"
std::string
mod::QuestionManager::retestQuestions() noexcept
{
    // auto connection = data::ConnectionManager::getUserConnection();
    // auto temp       = connection.val.getDataArray<data::Question>();
    // std::unordered_map<int, data::Question> questions;
    // for (auto&& i : temp)
    // {
    //     questions[i.id] = std::move(i);
    // }

    // auto answers = connection.val.getDataArray<data::Answer>();
    // for (auto& a : answers)
    // {
    //     if (a.questionID == 30)
    //     {
    //         int yy = 0;
    //         ++yy;
    //     }

    //     auto& q = questions[a.questionID];
    //     if (q.type == "table")
    //     {
    //         if (a.questionID == 30 && a.value == "13467810")
    //         {
    //             int yy = 0;
    //             ++yy;
    //         }

    //         a.verdict = "P";
    //         a.weight  = 0;

    //         auto jAns = text::Parser::slice(q.juryAnswer, ",");
    //         auto pAns = text::Parser::slice(a.value, ", ;.");

    //         bool ggFlag = jAns[0].back() >= '0' && jAns[0].back() <= '9';
    //         if (ggFlag && pAns.size() == 1 && pAns[0].size() > 1)
    //         {
    //             std::string ghgh;
    //             for (auto& i : pAns[0])
    //             {
    //                 ghgh += std::string({i}) + ",";
    //             }
    //             pAns = text::Parser::slice(ghgh, ", ;.");
    //         }

    //         if (!ggFlag || pAns.size() < jAns.size())
    //         {
    //             pAns.resize(jAns.size());
    //         }

    //         std::unordered_set<std::wstring> ggAnss;

    //         for (int i = 0; i < jAns.size(); ++i)
    //         {
    //             auto jAnsStr = dom::Cyrilic::global.toWString(jAns[i]);
    //             dom::Cyrilic::global.standardProcedure(jAnsStr);
    //             if (ggFlag)
    //             {
    //                 ggAnss.insert(jAnsStr);
    //                 continue;
    //             }

    //             auto pAnsStr = dom::Cyrilic::global.toWString(pAns[i]);
    //             dom::Cyrilic::global.standardProcedure(pAnsStr);

    //             if (pAnsStr == jAnsStr)
    //             {
    //                 a.weight += q.weight;
    //             }
    //         }

    //         if (ggFlag)
    //         {
    //             for (int i = 0; i < jAns.size(); ++i)
    //             {
    //                 auto pAnsStr = dom::Cyrilic::global.toWString(pAns[i]);
    //                 dom::Cyrilic::global.standardProcedure(pAnsStr);

    //                 if (ggAnss.count(pAnsStr))
    //                 {
    //                     a.weight += q.weight;
    //                 }
    //                 else
    //                 {
    //                     a.weight -= q.weight;
    //                 }
    //             }
    //         }

    //         if (a.weight <= 0) a.weight = -1;
    //     }
    //     else
    //     {
    //         auto pAnsStr = dom::Cyrilic::global.toWString(a.value);
    //         dom::Cyrilic::global.standardProcedure(pAnsStr);

    //         auto jAnsStr = dom::Cyrilic::global.toWString(q.juryAnswer);
    //         dom::Cyrilic::global.standardProcedure(jAnsStr);

    //         a.verdict = (pAnsStr == jAnsStr) ? "T" : "F";
    //         if (a.verdict == "T")
    //         {
    //             a.weight = 1;
    //         }
    //         else
    //         {
    //             a.weight = -1;
    //         }
    //     }
    // }

    // connection.val.write(answers);

    return "?";
}
