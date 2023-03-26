#include "mark_handler.hpp"

crow::json::wvalue
post::MarkHandler::process(const crow::request& aReq)
{
    data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
    auto req  = crow::json::load(aReq.body);
    auto mark = parseRequest<data::Mark>(req).table;
    if (mark[0].lesson_id == 0)
    {
        mark[0].lesson_id =
            dbq.getData<data::Mark>("id = " + data::wrap(mark[0].id))[0]
                .lesson_id;
    }
    auto lesson =
        dbq.getData<data::Lesson>("id = " + data::wrap(mark[0].lesson_id));
    mark[0].journal_table_id = lesson[0].journal_table_id;
    dbq.update(mark);
    return {mark[0].id};
}