#include "print_journal.hpp"

#include <unordered_map>
#include <vector>

#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

std::string
post::PrintJournal::process(const std::string& aData) noexcept
{
    std::string result;

    int num = std::stoi(aData);

    std::string output;
    output += file::File::getAllData(
        file::Path::getPathUnsafe("resource", "header.tex"), true);
    output += makeJournal(num);
    output += "\\end{document}";

    result = file::File::writeData("print", "j.tex", output).value();
    result = result.substr(result.find("data") + 5);

    return result;
}

std::string
post::PrintJournal::makeJournal(int aID) noexcept
{
    std::string result;

    data::JournalTable journal;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        journal =
            connection.val.getData<data::JournalTable>("id=" + data::wrap(aID));
    }

    auto attendance = makeAttendance(journal);
    while (!attendance.empty())
    {
        result += attendance.getNextAttendance();
        result += attendance.getNextLessons();
    }

    return result;
}

post::Attendance
post::PrintJournal::makeAttendance(const data::JournalTable& aJournal) noexcept
{
    Attendance attendance(aJournal.gradeID, limit);

    auto connection = data::ConnectionManager::getUserConnection();
    auto lessons    = connection.val.getDataArray<data::Lesson>(
        "journal_table_id=" + data::wrap(aJournal.id));
    auto teacher = connection.val.getData<data::User>(
        "id=" + data::wrap(aJournal.teacherID));

    auto last = dom::DateAndTime::getDate(lessons[0].dateVal);
    int cnt   = 0;
    attendance.newPage(last.month().as_number());
    for (auto& l : lessons)
    {
        auto cur = dom::DateAndTime::getDate(l.dateVal);
        if (cur.month() != last.month() || cnt >= limit)
        {
            attendance.newPage(cur.month().as_number());
            cnt = 0;
        }

        auto theme =
            connection.val.getData<data::Theme>("id=" + data::wrap(l.themeID));

        attendance.emplaceLesson(cur.day().as_number(), theme.name,
                                 teacher.surname);
        last = cur;

        auto marks = connection.val.getDataArray<data::Mark>("lesson_id=" +
                                                             data::wrap(l.id));
        for (auto& m : marks)
        {
            attendance.setMark(m.studentID, cnt, m.markValue);
        }

        ++cnt;
    }

    attendance.reverse();

    return attendance;
}
