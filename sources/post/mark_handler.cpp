#include "mark_handler.hpp"

#include "database/connection_manager.hpp"

crow::json::wvalue
post::MarkHandler::process(PostRequest<data::Mark>& aReq) noexcept
{
    auto& mark      = aReq.data;
    auto connection = data::ConnectionManager::getUserConnection();

    if (mark.lesson_id == 0)
    {
        mark.lesson_id =
            connection.val.getData<data::Mark>("id = " + data::wrap(mark.id))
                .lesson_id;
    }

    auto lesson = connection.val.getData<data::Lesson>(
        "id = " + data::wrap(mark.lesson_id));
    mark.journal_table_id = lesson.journal_table_id;
    connection.val.write(mark);
    return {mark.id};
}