#include "result_generator.hpp"

#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "domain/cyrillic.hpp"
#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"

std::wstring
foox2(const std::string& aStr)
{
    // std::string ansStr = file::Parser::slice(answer.value, "", " \t\n.,;");
    auto wStr = dom::Cyrilic::global.toWString(aStr);
    dom::Cyrilic::global.standardProcedure(wStr);
    return wStr;
}

int
equal(const std::string& aStr1,
      const std::string& aStr2,
      std::set<std::string>& wrong)
{
    auto ans = file::Parser::slice(aStr2, "/"s);

    int result = 0;
    for (auto& i : ans)
    {
        if (foox2(aStr1) == foox2(i))
        {
            result = 1;
        }
    }
    if (!result)
    {
        result = -1;
        wrong.emplace(aStr1);
    }
    return result;
}

int
partly(const std::string& aStr1,
       const std::string& aStr2,
       std::set<std::string>& wrong)
{
    int result = 0;
    if (aStr1.size() != aStr2.size())
    {
        wrong.emplace(aStr1);
        return 0;
    }

    for (int i = 0; i < aStr1.size(); ++i)
    {
        if (aStr1[i] == aStr2[i]) ++result;
        else
        {
            wrong.emplace(std::to_string(i + 1) + "-" + aStr1[i]);
        }
    }
    if (result) --result;
    return result;
}

int
slova(const std::string& aStr1,
      const std::string& aStr2,
      std::set<std::string>& wrong)
{
    int result = 0;

    auto usr = file::Parser::slice(aStr1, " ,."s);
    auto ans = file::Parser::slice(aStr2, " ,."s);
    std::unordered_set<std::wstring> ans_s;
    for (auto& i : ans)
    {
        ans_s.emplace(foox2(i));
    }

    auto s2 = foox2(aStr2);
    for (auto& i : usr)
    {
        if (ans_s.count(foox2(i)))
        {
            ++result;
        }
        else
        {
            wrong.emplace(i);
        }
    }
    return result;
}

std::string
core::ResultGenerator::generate(int aCompetitionID) noexcept
{
    // std::set<int> qr = {1,32,33,34,35,36,39,40,41,44,45,56,58,60};

    auto connection = data::ConnectionManager::getUserConnection();
    // auto competition =
    //     connection.val.getData<data::Competition>("id=" + aCompetitionName);

    auto questionIDs = connection.val.getDataArray<data::CompetitionQuestion>(
        "competition_id=" + data::wrap(aCompetitionID));

    std::string cond;
    for (auto& i : questionIDs)
        cond += "id=" + std::to_string(i.questionID) + " OR ";
    cond.resize(cond.size() - 4);
    auto questions = connection.val.getDataArray<data::Question>(cond);

    std::vector<std::set<std::string>> wrong(questions.size());

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

    std::unordered_map<std::string, std::vector<int>> resultTable;
    for (auto& u : users)
    {
        auto user =
            connection.val.getData<data::User>("id=" + data::wrap(u.userID));

        resultTable[user.login].resize(questions.size());
        for (int i = 0; i < questions.size(); ++i)
        {
            auto& q = questions[i];
            if (q.type == "text") continue;

            auto answer = connection.val.getData<data::Answer>(
                "user_id=" + data::wrap(user.id) +
                " AND "
                "question_id=" +
                data::wrap(q.id));
            if (answer.id)
            {
                // if (qr.count(questions[i].id))
                // {
                //     resultTable[user.login][i] = partly(answer.value,
                //     questions[i].juryAnswer);
                // }
                if (q.type == "singl")
                {
                    resultTable[user.login][i] =
                        equal(answer.value, questions[i].juryAnswer, wrong[i]);
                }
                else if (q.type == "sootv")
                {
                    resultTable[user.login][i] =
                        partly(answer.value, questions[i].juryAnswer, wrong[i]);
                }
                else if (q.type == "predl")
                {
                    resultTable[user.login][i] =
                        equal(answer.value, questions[i].juryAnswer, wrong[i]);
                }
                else if (q.type == "slova")
                {
                    resultTable[user.login][i] =
                        slova(answer.value, questions[i].juryAnswer, wrong[i]);
                }
            }
        }
    }

    std::string data;
    for (auto& i : resultTable)
    {
        data += i.first + " ";
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

    for (int i = 0; i < wrong.size(); ++i)
    {
        auto& q = questions[i];
        if (q.type == "text") continue;

        auto& data = wrong[i];
        std::cout << i + 1;

        std::cout << ": '" << questions[i].juryAnswer << "' ";

        std::cout << " - [";
        bool flag = false;
        for (auto& j : data)
        {
            if (flag) std::cout << ", ";
            flag = true;

            std::cout << "'" << j << "'";
        }
        std::cout << "]";

        std::cout << "\n ";
    }

    return file::File::writeData(
               "print",
               "results_" + std::to_string(aCompetitionID) + "_" +
                   dom::DateAndTime::getCurentTimeSafe() + ".txt",
               data)
        .value();
    // return std::to_string(resultTable.begin()->second[10]);
}
