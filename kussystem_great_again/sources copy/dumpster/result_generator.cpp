#include "result_generator.hpp"

#include <fstream>
#include <string>
#include <unordered_map>

#include "domain/cyrillic.hpp"
#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"

std::wstring
foox2(const char* aStr)
{
    // str::String ansStr = file::Parser::slice(answer.value, "", " \t\n.,;");
    auto wStr = dom::Cyrilic::global.toWString(aStr);
    dom::Cyrilic::global.standardProcedure(wStr);
    return wStr;
}

int
equal(const char* aStr1, const char* aStr2)
{
    int result = 1;
    if (foox2(aStr1) != foox2(aStr2))
    {
        result = -1;
    }
    return result;
}
int
partly(const char* aStr1, const char* aStr2)
{
    int result = 0;
    auto s1    = foox2(aStr1);
    auto s2    = foox2(aStr2);
    for (int i = 0; i < s1.size(); ++i)
    {
        if (s1[i] == s2[i]) ++result;
    }
    return result;
}
#include <set>
str::String
core::ResultGenerator::generate(int aCompetitionID) noexcept
{
    std::set<int> qr = {1, 32, 33, 34, 35, 36, 39, 40, 41, 44, 45, 56, 58, 60};

    auto connection = data::ConnectionManager::getUserConnection();
    // auto competition =
    //     connection.val.getData<data::Competition>("id=" + aCompetitionName);

    auto questionIDs = connection.val.getDataArray<data::CompetitionQuestion>(
        "competition_id=" + data::wrap(aCompetitionID));
    str::String cond;
    for (auto& i : questionIDs)
        cond += "id=" + std::to_string(i.questionID) + " OR ";
    cond.resize(cond.size() - 4);
    auto questions = connection.val.getDataArray<data::Question>(cond);

    // data::DataArray<data::Question> questions;
    // for(auto& i : questionIDs)
    // {
    //     questions.emplace_back();
    //     auto qq = connection.val.getDataArray<data::Question>();
    //     //  "id=" + data::wrap(i.questionID))
    //     questions.emplace_back(std::move(qq));
    // }
    auto users = connection.val.getDataArray<data::CompetitionUser>(
        "competition_id=" + data::wrap(aCompetitionID));

    std::unordered_map<str::String, std::vector<int>> resultTable;
    for (auto& u : users)
    {
        auto user =
            connection.val.getData<data::User>("id=" + data::wrap(u.userID));

        resultTable[user.login].resize(questions.size());
        for (int i = 0; i < questions.size(); ++i)
        {
            auto answer = connection.val.getData<data::Answer>(
                "user_id=" + data::wrap(user.id) +
                " AND "
                "question_id=" +
                data::wrap(questions[i].id));
            if (answer.id)
            {
                if (qr.count(questions[i].id))
                {
                    resultTable[user.login][i] =
                        partly(answer.value, questions[i].juryAnswer);
                }
                else
                {
                    resultTable[user.login][i] =
                        equal(answer.value, questions[i].juryAnswer);
                }
            }
        }
    }

    str::String data;
    for (auto& i : resultTable)
    {
        data += i.first + " = ";
        for (auto& j : i.second)
        {
            data += std::to_string(j) + " ";
        }

        int sum = 0;
        for (auto j : i.second)
        {
            sum += j > 0 ? j : 0;
        }
        data += " = " + std::to_string(sum) + "\n";
    }
    return file::File::writeData(
               "print",
               "results_" + std::to_string(aCompetitionID) + "_" +
                   dom::DateAndTime::getCurentTimeSafe() + ".txt",
               data)
        .value();
    // return std::to_string(resultTable.begin()->second[10]);
}
