#include "result_generator.hpp"

#include <fstream>
#include <string>
#include <unordered_map>

#include "database/connection_manager.hpp"

void
core::ResultGenerator::generate(int aCompetitionID) noexcept
{
    // auto connection = data::ConnectionManager::getUserConnection();
    // // auto competition =
    // //     connection.val.getData<data::Competition>("id=" + aCompetitionName);

    // auto problems = connection.val.getTable<data::CompetitionProblem>(
    //     "competition_id=" + data::wrap(aCompetitionID));
    // auto users = connection.val.getTable<data::User_competition>(
    //     "competition_id=" + data::wrap(aCompetitionID));

    // std::unordered_map<std::string, std::map<int, int>> resultTable;

    // for (auto& i : users)
    // {
    //     auto user =
    //         connection.val.getData<data::User>("id=" + data::wrap(i.userID));
    //     if (user.id == 0) continue;

    //     if (user[0].login == "rostizm2008@gmail.com")
    //     {
    //         int yy = 0;
    //         yy++;
    //     }
    //     for (auto& j : problems)
    //     {
    //         auto submissions = connection.val.getTable<data::Submission>(
    //             "user_id=" + data::wrap(i.userID) +
    //             " AND "
    //             "problem_id=" +
    //             data::wrap(j.id));

    //         bool flag = false;
    //         for (auto& k : submissions)
    //         {
    //             resultTable[user[0].login][j.problem_id]--;
    //             flag = k.verdict == "OK";
    //         }
    //         if (flag) resultTable[user[0].login][j.problem_id] *= -1;
    //     }
    // }

    // std::ofstream resultFile("result.out");
    // for (auto& i : resultTable)
    // {
    //     resultFile << i.first;
    //     int task    = 0;
    //     int penalty = 0;
    //     for (auto& j : problems)
    //     {
    //         resultFile << '\t';
    //         if (i.second[j.problem_id] > 0)
    //             resultFile << '+' << i.second[j.problem_id];
    //         else if (i.second[j.problem_id] < 0)
    //             resultFile << i.second[j.problem_id];
    //         else resultFile << '*';

    //         if (i.second[j.problem_id] > 0)
    //         {
    //             penalty += i.second[j.problem_id];
    //             task++;
    //         }
    //     }

    //     resultFile << '\t' << task << "\t" << penalty;
    //     resultFile << '\n';
    // }
}