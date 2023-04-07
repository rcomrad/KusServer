#include "question_handler.hpp"

crow::json::wvalue
get::UserHandler::process(const std::vector<int>& aColumn,
                          data::SmartConnection& aConnection) noexcept
{
    auto table = aConnection.val.select2<data::User>(aColumn);
    // table.turnOffColumn("jury_answer");

    return result;
}
