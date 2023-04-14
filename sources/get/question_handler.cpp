#include "question_handler.hpp"

#include "file/file.hpp"
#include "file/path.hpp"

crow::json::wvalue
get::QuestionHandler::process(int aQuestionID, int aUserId) noexcept
{
    crow::json::wvalue result;

    data::Table<data::Question> table;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        table           = connection.val.getData<data::Question>("id=" +
                                                       data::wrap(aQuestionID));
    }

    table.turnOffColumn("jury_answer");

    auto path = file::Path::getInstance().getPath("question");
    if (path)
    {
        auto legend = file::File::getAllData(path.value() + table[0].nickname +
                                             "/legend.txt");

        table.turnOffColumn("nickname");
        auto tableList      = getTableAsList(table)[0];
        tableList["legend"] = std::move(legend);

        data::Table<data::Answer> answer;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            answer          = connection.val.getData<data::Answer>(
                "user_id=" + data::wrap(aUserId) + " AND " +
                "question_id=" + data::wrap(aQuestionID));
        }
        if (answer.size())
        {
            tableList["answer"]  = std::move(answer.back().value);
            tableList["verdict"] = std::move(answer.back().value);
        }

        result["question"] = std::move(tableList);
    }
    return result;
}
