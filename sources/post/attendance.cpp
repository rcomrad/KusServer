#include "attendance.hpp"

#include <algorithm>

#include "database/connection_manager.hpp"
#include "database/database_structures.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "tex_manager/tex_table.hpp"

post::Attendance::Attendance(int aID, int aSize) noexcept : size(aSize)
{
    auto connection    = data::ConnectionManager::getUserConnection();
    auto grade_student = connection.val.getDataArray<data::GradeStudent>(
        "grade_id=" + data::wrap(aID));

    for (auto& i : grade_student)
    {
        auto student =
            connection.val.getData<data::User>("id=" + data::wrap(i.studentID));
        // names[student.id]               = student.surname + " " +
        // student.name; orderedNames[names[student.id]] = student.id;
        orderedNames[student.surname + " " + student.name] = student.id;
    }

    int cnt        = 2e9;
    std::string gg = " ";
    while (orderedNames.size() < 30)
    {
        orderedNames[gg] = ++cnt;
        gg += " ";
    }
}

void
post::Attendance::setMark(int aStudentId,
                          int aDateNum,
                          const std::string& aMark) noexcept
{
    attendance.back()[aStudentId][aDateNum] = aMark;
}

void
post::Attendance::newPage(uint8_t aMounth) noexcept
{
    curMounth = aMounth;

    auto& temp = attendance.emplace_back();
    for (auto& i : orderedNames)
    {
        temp[i.second].resize(size);
    }

    dates.emplace_back();
    themes.emplace_back();

    months.emplace_back(std::to_string(aMounth));
}

void
post::Attendance::emplaceLesson(uint8_t aDate,
                                const std::string& aTheme,
                                const std::string& aTeacher) noexcept
{
    std::string date = std::to_string(aDate);

    if (!dates.back().empty()) dates.back() += "&";
    dates.back() += date;

    if (!themes.back().empty()) themes.back() += "\n\\\\ \\hline\n";
    themes.back() += date + "."s + (curMounth < 10 ? "0"s : ""s) +
                     std::to_string(curMounth) + "&" + aTheme + "&2&" +
                     aTeacher + "&";
}

void
post::Attendance::addFiller() noexcept
{
    if (!dates.back().empty()) dates.back() += "&";
    dates.back() += " ";
}

void
post::Attendance::reverse() noexcept
{
    std::reverse(attendance.begin(), attendance.end());
    std::reverse(dates.begin(), dates.end());
    std::reverse(themes.begin(), themes.end());
    std::reverse(months.begin(), months.end());
}

std::string
post::Attendance::getNextAttendance() noexcept
{
    static auto monthNums = file::File::getWordsMap(
        file::Path::getPathUnsafe("resource", "month.txt"), true);

    // static auto journalDate = file::File::getAllData(
    //     file::Path::getPathUnsafe("resource", "attendance.tex"), true);
    // std::string result = journalDate;

    tex::TexTable table({
        {tex::ColumnType::Centr},
        {tex::ColumnType::ParagraphLeft, 5},
        {tex::ColumnType::ParagraphCentr, 0.4, 15}
    });

    table.setWithCount("УЧЁТ ПОСЕЩАЕМОСТИ И ВЫПОЛНЕНИЯ", tex::ColumnType::Right,
                       17, tex::ColumnBorders::Nun);
    table.newLine();

    table.setWithRange("Месяц", tex::ColumnType::Left, 3, 9,
                       tex::ColumnBorders::Nun);
    table.setWithRange(monthNums[months.back()], tex::ColumnType::Right, 9,
                       tex::ColumnBorders::Right);
    months.pop_back();
    table.newLine(3, 17);

    table.pushBack("№");
    table.pushBack("Фамилия, имя обучающегося");
    table.setWithRange("Дата", tex::ColumnType::Centr, 2,
                       tex::ColumnBorders::Right);
    table.newLine(3, 17);

    table.pushBack("");
    table.pushBack("");
    table.add("&");
    table.add(dates.back());
    dates.pop_back();
    table.newLine();

    int cnt = 1;
    for (auto& flag : {false, true})
    {
        for (auto& i : orderedNames)
        {
            if (i.first[0] == ' ' ^ flag) continue;

            int id                  = i.second;
            const std::string& name = i.first;

            table.pushBack(cnt);
            table.pushBack(name);
            for (auto& j : attendance.back()[id])
            {
                table.pushBack(j);
            }
            table.newLine();

            ++cnt;
        }
    }
    attendance.pop_back();

    table.finish();
    std::string result = "\n" + table.get() + "\\clearpage\n";

    return result;
}

std::string
post::Attendance::getNextLessons() noexcept
{
    static auto paln = file::File::getAllData(
        file::Path::getPathUnsafe("resource", "plan.tex"), true);
    std::string result = paln;

    result += themes.back();
    result += "\n\\\\ \\hline\n";
    result += "\n\\end{tabular}\n";
    themes.pop_back();

    result += "\\clearpage\n";

    return result;
}

bool
post::Attendance::empty() const noexcept
{
    return attendance.empty();
}
