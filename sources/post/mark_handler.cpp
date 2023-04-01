#include "mark_handler.hpp"

#include "database/connection_manager.hpp"

crow::json::wvalue
post::MarkHandler::process(const crow::request& aReq)
{
    auto connection = data::ConnectionManager::getUserConnection();
    auto req        = crow::json::load(aReq.body);
    auto mark       = parseRequest<data::Mark>(req).table;
    if (mark[0].lesson_id == 0)
    {
        mark[0].lesson_id =
            connection.val
                .getData<data::Mark>("id = " + data::wrap(mark[0].id))[0]
                .lesson_id;
    }
    auto lesson = connection.val.getData<data::Lesson>(
        "id = " + data::wrap(mark[0].lesson_id));
    mark[0].journal_table_id = lesson[0].journal_table_id;
    connection.val.update(mark);
    return {mark[0].id};
}