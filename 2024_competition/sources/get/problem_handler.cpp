#include "problem_handler.hpp"

#include "domain/url_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
void
loadProblem(crow::json::wvalue& aProblem,
            std::string aName,
            int exampesCount) noexcept
{
    static std::string problemFolderPath =
        file::Path::getPath("problem").value();
    auto currentProblemPath = problemFolderPath + aName;

    // std::string rrr;
    // static const std::unordered_set<std::string> excludedFiles = {
    //     "checker.cpp", "input_format.txt", "legend.txt", "output_format.txt",
    //     "testlib.h"};
    // auto data = file::Path::getContentMap(problemFolderPath);
    // for (auto& i : data)
    // {
    //     if (excludedFiles.count(i.first)) continue;

    //     if (i.first.find(".gif") != -1 || i.first.find(".png") != -1 ||
    //         i.first.find(".PNG") != -1 || i.first.find(".jpg") != -1)
    //     {
    //         rrr = dom::UrlWrapper::toHTMLSrc("problem/" + problemFolderPath +
    //                                          "/" + i.first);
    //     }
    // }

    aProblem["legend"] =
        file::File::getAllData(currentProblemPath + "/legend.txt");
    aProblem["input_format"] =
        file::File::getAllData(currentProblemPath + "/input_format.txt");
    aProblem["output_format"] =
        file::File::getAllData(currentProblemPath + "/output_format.txt");

    auto problemTestsPath = currentProblemPath + "/test/";
    crow::json::wvalue::list exampleList;
    for (int i = 1; i <= exampesCount; ++i)
    {
        std::string ns = dom::toString(i);
        if (ns.size() < 2) ns = "0" + ns;
        crow::json::wvalue example;
        example["input"] = file::File::getAllData(problemTestsPath + ns + "");
        example["output"] =
            file::File::getAllData(problemTestsPath + ns + ".a");
        exampleList.push_back(std::move(example));
    }
    aProblem["tests"] = std::move(exampleList);
}

crow::json::wvalue
getProblemJson(int aProblemId)
{
    data::Problem problem;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        problem         = connection.val.getData<data::Problem>(
            "id=" + dom::toString(aProblemId));
    }
    auto result = problem.getAsJson();
    loadProblem(result, problem.nickname, problem.exampleCount);
    return result;
}

std::vector<crow::json::wvalue>
getAllProblems()
{
    data::DataArray<data::Problem> problems;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        problems        = connection.val.getDataArray<data::Problem>();
    }

    std::vector<crow::json::wvalue> result;
    for (auto& i : problems)
    {
        while (i.id > result.size()) result.emplace_back();
        result.push_back(getProblemJson(i.id));
    }

    return result;
}

crow::json::wvalue
get::ProblemHandler::process(int aProblemID, int aUserID) noexcept
{
    static auto problemArray = getAllProblems();

    crow::json::wvalue result = problemArray[aProblemID];

    data::DataArray<data::Submission> submission;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        submission      = connection.val.getDataArray<data::Submission>(
            "user_id=" + dom::toString(aUserID) + " and " +
            "problem_id=" + dom::toString(aProblemID));
    }
    result["submission"] = submission.getAsJList();

    return result;
}
