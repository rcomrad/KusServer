#include "competition_question_handler.hpp"

#include "domain/date_and_time.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
// std::string get::CompetitionHandler::mProblemPath =
//     dom::Path::getInstance().getPath("problem").value();

// boost::posix_time::ptime
// foott()
// {
//     auto time = file::File::getAllData("data", "time.txt");
//     return dom::DateAndTime::getTime(time);
// }

crow::json::wvalue
get::CompetitionQuestionHandler::process(
    const std::unordered_set<int>& aColumn,
    data::SmartConnection& aConnection) noexcept
{
    // static auto time = foott();

    crow::json::wvalue result;
    // if (dom::DateAndTime::getRawCurentTime() > time)
    // {
        auto table     = aConnection.val.getNextDataArray<data::Form>(aColumn);
        auto tableList = table.getAsJList();
        result["competition_question"] = std::move(tableList);
    // }
    // else
    // {
    //     result["error"]                = dom::DateAndTime::getCurentTime();
    //     result["competition_question"] = "error";
    // }

    return result;

    // data::Table<data::Competition> competition;
    // data::Table<data::CompetitionProblem> problemIDs;

    // std::vector<data::Table<data::Problem>> problems;
    // std::vector<data::Table<data::Submission>> submissions;

    // {
    //     std::vector<std::string> empty;
    //     std::vector<std::string> probV = {"3", "4", " 5"};
    //     auto connection = data::ConnectionManager::getUserConnection();

    //     competition = connection.val.select<data::Competition>(
    //         empty, "id=" + data::wrap(aCompetitionID));
    //     problemIDs = connection.val.select<data::CompetitionProblem>(
    //         empty, "competition_id=" + data::wrap(aCompetitionID));

    //     std::vector<data::Table<data::Problem>> p(problemIDs.size());
    //     std::vector<data::Table<data::Submission>> s(problemIDs.size());

    //     int cnt = 0;
    //     for (auto& i : problemIDs)
    //     {
    //         auto problemTemp = connection.val.select<data::Problem>(
    //             empty, "id=" + data::wrap(i.problem_id));
    //         p[cnt] = std::move(problemTemp);

    //         auto submissionTemp = connection.val.select<data::Submission>(
    //             empty, "problem_id=" + data::wrap(i.problem_id) + " AND " +
    //                        "user_id=" + data::wrap(aUserID));
    //         s[cnt] = std::move(submissionTemp);
    //         ++cnt;
    //     }

    //     problems    = std::move(p);
    //     submissions = std::move(s);
    // }

    // auto result = getTableAsList(competition)[0];
    // crow::json::wvalue::list problemList;
    // for (int i = 0; i < problems.size(); ++i)
    // {
    //     problems[i].turnOffColumn("test_count");
    //     problems[i].turnOffColumn("nickname");
    //     problems[i].turnOffColumn("checker_name");
    //     problems[i].turnOffColumn("example_count");

    //     submissions[i].turnOffColumn("user_id");
    //     submissions[i].turnOffColumn("problem_id");
    //     submissions[i].turnOffColumn("source_name");

    //     auto probJ          = getTableAsList(problems[i])[0];
    //     probJ["submission"] = getTableAsList(submissions[i]);
    //     probJ["legend"]     = dom::FileReader::getAllData(
    //         mProblemPath + problems[i][0].nickname + "/legend.txt", true);
    //     probJ["input_format"] = dom::FileReader::getAllData(
    //         mProblemPath + problems[i][0].nickname + "/input_format.txt",
    //         true);
    //     probJ["output_format"] = dom::FileReader::getAllData(
    //         mProblemPath + problems[i][0].nickname + "/output_format.txt",
    //         true);

    //     crow::json::wvalue::list tests;
    //     for (int mTestNum = 1; mTestNum <= problems[i][0].example_count;
    //          ++mTestNum)
    //     {
    //         crow::json::wvalue temp;
    //         temp["input"] = dom::FileReader::getAllData(
    //             mProblemPath + problems[i][0].nickname + "/test/" +
    //                 std::to_string(mTestNum) + ".in",
    //             true);
    //         temp["output"] = dom::FileReader::getAllData(
    //             mProblemPath + problems[i][0].nickname + "/test/" +
    //                 std::to_string(mTestNum) + ".out",
    //             true);
    //         tests.emplace_back(std::move(temp));
    //     }
    //     probJ["tests"] = std::move(tests);

    //     problemList.emplace_back(std::move(probJ));
    // }
    // result["problems"] = std::move(problemList);

    return result;
}
