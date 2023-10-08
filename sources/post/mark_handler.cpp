#include "mark_handler.hpp"

#include "database/connection_manager.hpp"

#include "database/safe_sql_wrapper.hpp"

crow::json::wvalue
post::MarkHandler::process(post::PostRequest<data::Mark>& aReq) noexcept
{
    auto& mark      = aReq.data;
    auto connection = data::ConnectionManager::getUserConnection();

    if (mark.lessonID == 0)
    {
        mark.lessonID =
            connection.val
                .getData<data::Mark>("id = " + data::safeWrap(mark.id))
                .lessonID;
    }

    auto lesson = connection.val.getData<data::Lesson>(
        "id = " + data::safeWrap(mark.lessonID));
    mark.journalTableID = lesson.journalTableID;
    connection.val.write(mark);
    return {mark.id};
}
