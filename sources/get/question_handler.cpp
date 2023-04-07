#include "question_handler.hpp"

crow::json::wvalue
get::QuestionHandler::process(const std::vector<int>& aColumn,
                              data::SmartConnection& aConnection) noexcept
{
    crow::json::wvalue result;
    auto table = aConnection.val.select2<data::User>(aColumn);
    // table.turnOffColumn("jury_answer");

    return result;
}
