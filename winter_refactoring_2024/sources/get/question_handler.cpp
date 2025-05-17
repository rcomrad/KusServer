#include "question_handler.hpp"

#include <mutex>
#include <unordered_map>

#include "general_tools/log.hpp"
#include "domain/url_wrapper.hpp"

#include "text_data/file.hpp"
#include "text_data/path.hpp"

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
        // answer.value.pop_back();
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
        LOG_INFO("Loading question #", aQuestionID);
        result = loadQuestion(aQuestionID);
    }
    return result;
}

crow::json::wvalue
get::QuestionHandler::loadQuestion(int aQuestionID) const noexcept
{
    static const std::unordered_set<std::string> excludedFiles = {"legend.txt",
                                                                  "data.txt"};

    data::Question question;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        question        = connection.val.getData<data::Question>(
            "id=" + data::wrap(aQuestionID));
    }
    auto result = question.getAsJson({"nickname", "jury_answer"});

    auto path = text::Path::getPath("question");
    if (path)
    {
        std::string legend;

        std::string folder = path.value() + question.nickname;
        auto fileData      = text::File::getLines(folder + "/legend.txt");
        for (auto& i : fileData)
        {
            legend += std::move(i);
            legend += " <br> ";
        }

        auto data = text::Path::getContentMap(folder);
        for (auto& i : data)
        {
            if (excludedFiles.count(i.first)) continue;

            else if (i.first == "ans_list.txt"
                     // &&
                     // (question.type == "multi" || question.type == "table")
            )
            {
                auto temp = text::File::getLines(i.second);
                crow::json::wvalue::list ans_list;
                for (auto& i : temp)
                {
                    ans_list.emplace_back(i);
                }
                result["ans_list"] = std::move(ans_list);
            }
            else if (i.first.find(".gif") != -1 || i.first.find(".png") != -1 ||
                     i.first.find(".PNG") != -1 || i.first.find(".jpg") != -1)
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

        // if (question.type == "table")
        // {
        //     auto rows = text::File::getLines(folder + "/rows.txt");
        //     crow::json::wvalue::list rowList;
        //     for (auto&& i : rows)
        //     {
        //         rowList.emplace_back(std::move(i));
        //     }
        //     result["inputDescription"] = std::move(rowList);
        // }
    }

    return result;
}
