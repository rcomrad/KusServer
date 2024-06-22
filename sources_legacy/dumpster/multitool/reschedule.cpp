#include "reschedule.hpp"

#include "database/connection_manager.hpp"

#include "post/journal_handler.hpp"
#include "server/request_unpacker.hpp"

//--------------------------------------------------------------------------------

std::string
mult::Reschedule::process(const crow::request& aReq) noexcept
{
    std::string result;

    crow::multipart::message msg(aReq);
    auto nameOpt = serv::RequestUnpacker::getPart(msg, "name");
    auto fromOpt = serv::RequestUnpacker::getPart(msg, "from");
    auto toOpt   = serv::RequestUnpacker::getPart(msg, "to");

    if (!nameOpt.has_value())
    {
        result = "Укажите название группы!";
    }
    else if (!fromOpt.has_value())
    {
        result = "Укажите дату переносимого занятия!";
    }
    else if (!toOpt.has_value())
    {
        result = "Укажите дату на которую производится перенос!";
    }
    else
    {
        // 1991-12-30
        data::Grade grade;
        data::JournalTable journal;
        data::Lesson lesson;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            grade =
                connection.val.getData<data::Grade>("name=" + nameOpt.value());
            journal = connection.val.getData<data::JournalTable>(
                "id=" + data::wrap(grade.id));
            lesson = connection.val.getData<data::Lesson>(
                "journal_table_id=" + data::wrap(journal.id) +
                " AND  date_val=" + fromOpt.value());
        }
        if (grade.id == 0)
        {
            result = "Данная группа отсутствует!";
        }
        else if (lesson.id == 0)
        {
            result = "Занятие по указанной дате отсутствует!";
        }
        else
        {
            post::JournalHandler::remakeSchedule(journal, data::wrap(lesson.id),
                                                 toOpt.value());
        }
    }

    return "1";
}
