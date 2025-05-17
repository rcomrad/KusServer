#include "print_journal.hpp"

#include <unordered_map>
#include <vector>

#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"
#include "database/safe_sql_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"

str::String
post::PrintJournal::process(const char* aData) noexcept
{
    str::String result;

    // int num = std::stoi(aData);

    // str::String name = dom::DateAndTime::getCurentTimeSafe();

    // str::String output;
    // output += file::File::getAllData(
    //     core::Path::getPathUnsafe("resource", "header.tex"), true);
    // output += makeJournal(num);
    // output += "\\end{document}";

    // result = file::File::writeData("print", name + ".tex", output).value();

    auto nums = file::Parser::slice(aData, " ");
    tex::TexFile outFile;
    for (auto i : nums)
    {
        makeJournal(outFile, std::stoi(i));
    }
    result = outFile.printToFile();

#ifdef LINUS_LINUX

    system(
        (core::Path::getPathUnsafe("pdf_compile.sh") + " "s + result).c_str());
    result = result.substr(result.find("print"), result.size());
    result.resize(result.size() - 3);
    result += "pdf";

#else

    result = result.substr(result.find("data") + 5);

#endif

    return result;
}

str::String
post::PrintJournal::makeJournal(tex::TexFile& aTexFile, int aID) noexcept
{
    str::String result;

    data::JournalTable journal;
    data::User teacher;
    data::Subject subject;
    data::Grade group;
    data::School school;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        journal         = connection.val.getData<data::JournalTable>(
            "id=" + data::safeWrap(aID));
        teacher = connection.val.getData<data::User>(
            "id=" + data::safeWrap(journal.teacherID));
        subject = connection.val.getData<data::Subject>(
            "id=" + data::safeWrap(journal.subjectID));
        group = connection.val.getData<data::Grade>(
            "id=" + data::safeWrap(journal.gradeID));
        school = connection.val.getData<data::School>(
            "id=" + data::safeWrap(teacher.schoolID));
    }

    auto attendance = makeAttendance(journal);

    aTexFile.setVariable("$attendance", attendance.getAttendance());
    aTexFile.setVariable("$lesson", attendance.getLessons());
    aTexFile.setVariable("$date", attendance.getDates());
    aTexFile.setVariable("$month", attendance.getMonths());

    aTexFile.setVariable("$teacher", std::vector<str::String>{
                                         teacher.surname + " " + teacher.name,
                                         teacher.surname + " " + teacher.name});
    aTexFile.setVariable("$subject",
                         std::vector<str::String>{subject.name, subject.name});
    aTexFile.setVariable(
        "$school", std::vector<str::String>{school.fullName, school.fullName});

    aTexFile.setVariable("$group", std::vector<str::String>{group.name});

    static auto week = file::File::getLines("week.txt");

    auto shedule = file::Parser::slice(journal.schedule, " ");

    str::String last              = "";
    std::vector<str::String> time = {"17.20-18.05", "18.15-19.00"};
    str::String weekTime;
    for (auto& i : shedule)
    {
        weekTime += week[std::stoi(i)];
        weekTime += "&"s + (i == last ? time[1] : time[0]);
        last = i;
        weekTime += "\\\\ \\hline\n";
    }
    aTexFile.setVariable("$schedule", std::vector<str::String>{weekTime});

    aTexFile.makeFromFIle("journal.textemp");

    return result;
}

post::Attendance
post::PrintJournal::makeAttendance(const data::JournalTable& aJournal) noexcept
{
    Attendance attendance(aJournal.gradeID, limit);

    auto connection = data::ConnectionManager::getUserConnection();
    auto lessons    = connection.val.getDataArray<data::Lesson>(
        "journal_table_id=" + data::safeWrap(aJournal.id));
    auto teacher = connection.val.getData<data::User>(
        "id=" + data::safeWrap(aJournal.teacherID));

    auto last = dom::DateAndTime::getDate(lessons[0].dateVal);
    int cnt   = 0;
    attendance.newPage(last.month().as_number());
    for (auto& l : lessons)
    {
        auto cur = dom::DateAndTime::getDate(l.dateVal);
        if (cur.month() != last.month() || cnt >= limit)
        {
            while (cnt < limit)
            {
                attendance.addFiller();
                ++cnt;
            }

            attendance.newPage(cur.month().as_number());
            cnt = 0;
        }

        auto theme = connection.val.getData<data::Theme>(
            "id=" + data::safeWrap(l.themeID));

        attendance.emplaceLesson(cur.day().as_number(), theme.name,
                                 teacher.surname);
        last = cur;

        auto marks = connection.val.getDataArray<data::Mark>(
            "lesson_id=" + data::safeWrap(l.id));
        for (auto& m : marks)
        {
            attendance.setMark(m.studentID, cnt, m.markValue);
        }

        ++cnt;
    }

    return attendance;
}

str::String
post::PrintJournal::makeFrontPage(const data::JournalTable& aJournal) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    auto teacher    = connection.val.getData<data::User>(
        "id=" + data::safeWrap(aJournal.teacherID));
    // auto plan =
    //     connection.val.getData<data::Plan>("id=" +
    //     data::wrap(aJournal.planID));
    auto subject = connection.val.getData<data::Subject>(
        "id=" + data::safeWrap(aJournal.subjectID));

    static auto front  = file::File::getAllData("resource", "front.tex");
    str::String result = front;

    auto numN    = result.find('N');
    result[numN] = ' ';
    result.insert(numN, subject.name);

    auto numT    = result.find('T');
    result[numT] = ' ';
    result.insert(numT, teacher.surname + " " + teacher.name);

    return result;
}
