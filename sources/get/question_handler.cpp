#include "question_handler.hpp"

#include <mutex>
#include <unordered_map>

#include "domain/log.hpp"
#include "domain/url_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

crow::json::wvalue
get::QuestionHandler::process(int aQuestionID, int aUserId) noexcept
{
    crow::json::wvalue temp = getInstance().getQuestion(aQuestionID);

    data::Answer answer;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        answer          = connection.val.getData<data::Answer>(
            "user_id=" + data::wrap(aUserId) + " AND " +
            "question_id=" + data::wrap(aQuestionID));
    }
    if (answer.id)
    {
        answer.value.pop_back();
        temp["answer"] = std::move(answer.value);
        // result["verdict"] = std::move(answer.verdict);
    }

    crow::json::wvalue result;
    result["question"] = std::move(temp);
    return result;
}

get::QuestionHandler::QuestionHandler() noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    auto questions  = connection.val.getDataArray<data::Question>();
    for (auto& i : questions)
    {
        mQuestions[i.id] = loadQuestion(i.id);
    }
}

get::QuestionHandler&
get::QuestionHandler::getInstance() noexcept
{
    static QuestionHandler instance;
    return instance;
}

crow::json::wvalue
get::QuestionHandler::getQuestion(int aQuestionID) const noexcept
{
    crow::json::wvalue result;
    auto it = mQuestions.find(aQuestionID);
    if (it != mQuestions.end())
    {
        result = crow::json::wvalue(it->second);
    }
    else
    {
        dom::writeInfo("Loading question #", aQuestionID);
        result = loadQuestion(aQuestionID);
    }
    return result;
}

crow::json::wvalue
get::QuestionHandler::loadQuestion(int aQuestionID) const noexcept
{
    data::Question question;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        question        = connection.val.getData<data::Question>(
            "id=" + data::wrap(aQuestionID));
    }
    auto result = question.getAsJson({"nickname", "jury_answer"});

    auto path = file::Path::getPath("question");
    if (path)
    {
        std::string legend;

        std::string folder = path.value() + question.nickname;
        auto fileData      = file::File::getLines(folder + "/legend.txt");
        for (auto& i : fileData)
        {
            legend += std::move(i);
            legend += " <br> ";
        }

        auto data = file::Path::getContentMap(folder);
        for (auto& i : data)
        {
            if (i.first == "legend.txt") continue;

            if (i.first.find(".gif") != -1 || i.first.find(".png") != -1 ||
                i.first.find(".jpg") != -1)
            {
                legend += dom::UrlWrapper::toHTMLSrc(
                    "question/" + question.nickname + "/" + i.first);
            }
            else
            {
                legend += dom::UrlWrapper::toHTMLHref(
                    "question/" + question.nickname + "/" + i.first);
            }
        }
        result["legend"] = std::move(legend);
    }

    return result;
}
