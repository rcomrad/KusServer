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

    auto path = file::Path::getPath("question");
    if (path)
    {
        auto temp   = question.getAsJson({"nickname"});
        auto legend = file::File::getAllData(path.value() + question.nickname +
                                             "/legend.txt");
        temp["legend"] = std::move(legend);

        data::Answer answer;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            answer          = connection.val.getData<data::Answer>(
                "user_id=" + data::wrap(aUserId) + " AND " +
                "questionID=" + data::wrap(aQuestionID));
        }
        if (answer.id)
        {
            temp["answer"]  = std::move(answer.value);
            temp["verdict"] = std::move(answer.value);
        }

        result["question"] = std::move(temp);
    }
    return result;
}
