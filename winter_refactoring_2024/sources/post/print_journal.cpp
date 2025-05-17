#include "print_journal.hpp"

#include <unordered_map>
#include <vector>

#include "database/connection_manager.hpp"
#include "database/safe_sql_wrapper.hpp"

#include "domain/date_time.hpp"

#include "text_data/file.hpp"
#include "text_data/parser.hpp"
#include "text_data/path.hpp"

std::string
post::PrintJournal::process(const std::string& aData) noexcept
{
    std::string result;

    // int num = std::stoi(aData);

    // std::string name = dom::TimeHandler::getCurentTime().getAllWSpaceSafe();

    // std::string output;
    // output += text::File::getAllData(
    //     text::Path::getPathUnsafe("resource", "header.tex"), true);
    // output += makeJournal(num);
    // output += "\\end{document}";

    // result = text::File::writeData("print", name + ".tex", output).value();

    auto nums = text::Parser::slice(aData, " ");
    tex::TexFile outFile;
    for (auto i : nums)
    {
        makeJournal(outFile, std::stoi(i));
    }
    result = outFile.printToFile();

#ifdef LINUS_LINUX

    system(
        (text::Path::getPathUnsafe("pdf_compile.sh") + " "s + result).c_str());
    result = result.substr(result.find("print"), result.size());
    result.resize(result.size() - 3);
    result += "pdf";

#else

    result = result.substr(result.find("data") + 5);

#endif

    return result;
}

std::string
post::PrintJournal::makeJournal(tex::TexFile& aTexFile, int aID) noexcept
{
    std::string result;

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

    aTexFile.setVariable("$teacher", std::vector<std::string>{
                                         teacher.surname + " " + teacher.name,
                                         teacher.surname + " " + teacher.name});
    aTexFile.setVariable("$subject",
                         std::vector<std::string>{subject.name, subject.name});
    aTexFile.setVariable(
        "$school", std::vector<std::string>{school.fullName, school.fullName});

    aTexFile.setVariable("$group", std::vector<std::string>{group.name});

    static auto week = text::File::getLines("week.txt");

    auto shedule = text::Parser::slice(journal.schedule, " ");

    std::string last              = "";
    std::vector<std::string> time = {"17.20-18.05", "18.15-19.00"};
    std::string weekTime;
    for (auto& i : shedule)
    {
        weekTime += week[std::stoi(i)];
        weekTime += "&"s + (i == last ? time[1] : time[0]);
        last = i;
        weekTime += "\\\\ \\hline\n";
    }
    aTexFile.setVariable("$schedule", std::vector<std::string>{weekTime});

    aTexFile.makeFromFIle("journal.textemp");

    return result;
}

post::Attendance
post::PrintJournal::makeAttendance(const data::JournalTable& aJournal) noexcept
{
    Attendance attendance(aJournal.gradeID, limit);

    // auto connection = data::ConnectionManager::getUserConnection();
    // auto lessons    = connection.val.getDataArray<data::Lesson>(
    //     "journal_table_id=" + data::safeWrap(aJournal.id));
    // auto teacher = connection.val.getData<data::User>(
    //     "id=" + data::safeWrap(aJournal.teacherID));

    // auto last = dom::DateTime::getDate(lessons[0].dateVal);
    // int cnt   = 0;
    // attendance.newPage(last.month().as_number());
    // for (auto& l : lessons)
    // {
    //     auto cur = dom::DateTime::getDate(l.dateVal);
    //     if (cur.month() != last.month() || cnt >= limit)
    //     {
    //         while (cnt < limit)
    //         {
    //             attendance.addFiller();
    //             ++cnt;
    //         }

    //         attendance.newPage(cur.month().as_number());
    //         cnt = 0;
    //     }

    //     auto theme = connection.val.getData<data::Theme>(
    //         "id=" + data::safeWrap(l.themeID));

    //     attendance.emplaceLesson(cur.day().as_number(), theme.name,
    //                              teacher.surname);
    //     last = cur;

    //     auto marks = connection.val.getDataArray<data::Mark>(
    //         "lesson_id=" + data::safeWrap(l.id));
    //     for (auto& m : marks)
    //     {
    //         attendance.setMark(m.studentID, cnt, m.markValue);
    //     }

    //     ++cnt;
    // }

    return attendance;
}

std::string
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

    static auto front  = text::File::getAllData("resource", "front.tex");
    std::string result = front;

    auto numN    = result.find('N');
    result[numN] = ' ';
    result.insert(numN, subject.name);

    auto numT    = result.find('T');
    result[numT] = ' ';
    result.insert(numT, teacher.surname + " " + teacher.name);

    return result;
}
