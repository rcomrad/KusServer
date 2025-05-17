#include "problem_handler.hpp"

#include "file/file.hpp"
#include "file/path.hpp"

crow::json::wvalue
get::ProblemHandler::process(const std::vector<int>& aColumn,
                             data::SmartConnection& aConnection) noexcept
{
    crow::json::wvalue result;
    return result;
}

crow::json::wvalue
get::ProblemHandler::getProblem(int aProblemID, int aUserID) noexcept
{
    crow::json::wvalue result;

    data::Table<data::Problem> problem;
    data::Table<data::Submission> submissions;

    {
        std::vector<std::string> empty;
        auto connection = data::ConnectionManager::getUserConnection();

        problem     = connection.val.getData<data::Problem>("id=" +
                                                        data::wrap(aProblemID));
        submissions = connection.val.getData<data::Submission>(
            "problem_id=" + data::wrap(aProblemID) + " AND " +
            "user_id=" + data::wrap(aUserID));
    }

    crow::json::wvalue::list problemList;

    problem.turnOffColumn("test_count");
    problem.turnOffColumn("nickname");
    problem.turnOffColumn("checker_name");
    problem.turnOffColumn("example_count");

    submissions.turnOffColumn("user_id");
    submissions.turnOffColumn("problem_id");
    submissions.turnOffColumn("source_name");

    auto problemPath = file::Path::getInstance().getPath("problem").value();

    auto probJ          = getTableAsList(problem)[0];
    probJ["submission"] = getTableAsList(submissions);
    probJ["legend"] = file::File::getAllData(problemPath + problem[0].nickname +
                                             "/legend.txt");
    probJ["input_format"] = file::File::getAllData(
        problemPath + problem[0].nickname + "/input_format.txt");
    probJ["output_format"] = file::File::getAllData(
        problemPath + problem[0].nickname + "/output_format.txt");

    crow::json::wvalue::list tests;
    for (int mTestNum = 1; mTestNum <= problem[0].example_count; ++mTestNum)
    {
        crow::json::wvalue temp;
        temp["input"] = file::File::getAllWithBr(
            problemPath + problem[0].nickname + "/test/" +
            std::to_string(mTestNum) + ".in");
        temp["output"] = file::File::getAllWithBr(
            problemPath + problem[0].nickname + "/test/" +
            std::to_string(mTestNum) + ".out");
        tests.emplace_back(std::move(temp));
    }
    probJ["tests"] = std::move(tests);

    problemList.emplace_back(std::move(probJ));

    result["problem"] = std::move(problemList);

    return result;
}