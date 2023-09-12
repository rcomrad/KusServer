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
        auto legend = file::File::getAllData(path.value() + question.nickname +
                                             "/legend.txt");
        temp["legend"] = std::move(legend);
    }

    result["question"] = std::move(temp);
    return result;
}
