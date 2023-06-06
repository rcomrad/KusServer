#include "user_question.hpp"

#include "question_handler.hpp"

// crow::json::wvalue
// get::UserQuestion::process(const std::vector<int>& aColumn,
//                            data::SmartConnection& aConnection) noexcept
// {
//     crow::json::wvalue result;

//     auto temp = QuestionHandler::process(aColumn, aConnection);

//     auto table = aConnection.val.select2<data::Question>(aColumn);
//     table.turnOffColumn("juryAnswer");


//         table.turnOffColumn("nickname");
//         auto tableList      = getTableAsList(table)[0];
//         tableList["legend"] = std::move(legend);

//         auto connection = data::ConnectionManager::getUserConnection();
//         auto answer     = connection.val.select<data::Answer>(
//             empty, "competition_id=" + data::wrap(aCompetitionID));
//         tableList["legend"] = std::move(legend);

//         result["question"] = std::move(tableList);

//     return result;
// }
