#include "question_handler.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

crow::json::wvalue
get::QuestionHandler::process(int aQuestionID, int aUserId) noexcept
{
    crow::json::wvalue result;

    data::Question question;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        question        = connection.val.getData<data::Question>(
            "id=" + data::wrap(aQuestionID));
    }

    auto temp = question.getAsJson({"nickname", "jury_answer"});
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
        temp["answer"]  = std::move(answer.value);
        temp["verdict"] = std::move(answer.verdict);
    }

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

            if (i.first.find(".gif") || i.first.find(".png") ||
                i.first.find(".jpg"))
                legend += " <img src=\"https://kusmirror.ru/question/" +
                          question.nickname + "/" + i.first + "\"/> ";
        }
        temp["legend"] = std::move(legend);
    }

    result["question"] = std::move(temp);
    return result;
}
