#include "attendance.hpp"

#include <algorithm>

#include "database/connection_manager.hpp"
#include "database/database_structures.hpp"
#include "database/safe_sql_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "tex_manager/tex_table.hpp"

post::Attendance::Attendance(int aID, int aSize) noexcept : size(aSize)
{
    auto connection    = data::ConnectionManager::getUserConnection();
    auto grade_student = connection.val.getDataArray<data::GradeStudent>(
        "grade_id=" + data::safeWrap(aID));

    for (auto& i : grade_student)
    {
        auto student = connection.val.getData<data::User>(
            "id=" + data::safeWrap(i.studentID));
        // names[student.id]               = student.surname + " " +
        // student.name; orderedNames[names[student.id]] = student.id;
        orderedNames[student.surname + " " + student.name] = student.id;
    }

    int cnt        = 2e9;
    str::String gg = " ";
    while (orderedNames.size() < 30)
    {
        orderedNames[gg] = ++cnt;
        gg += " ";
    }
}

void
post::Attendance::setMark(int aStudentId,
                          int aDateNum,
                          const char* aMark) noexcept
{
    attendance.back()[aStudentId][aDateNum] = aMark;
}

void
post::Attendance::newPage(uint8_t aMounth) noexcept
{
    static auto monthNums = file::File::getWordsMap("resource", "month.txt");

    curMounth = aMounth;

    auto& temp = attendance.emplace_back();
    for (auto& i : orderedNames)
    {
        temp[i.second].resize(size);
    }

    // while (dates.size() && dates.back().size() < 45)
    // {
    //     dates.back() += "  &";
    // }
    dates.emplace_back();
    themes.emplace_back();

    months.emplace_back(monthNums[std::to_string(aMounth)]);
}

void
post::Attendance::emplaceLesson(uint8_t aDate,
                                const char* aTheme,
                                const char* aTeacher) noexcept
{
    str::String date = std::to_string(aDate);

    if (!dates.back().empty()) dates.back() += "&";
    dates.back() += (date.size() == 1 ? " " : "") + date;

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

// void
// post::Attendance::reverse() noexcept
// {
//     std::reverse(attendance.begin(), attendance.end());
//     std::reverse(dates.begin(), dates.end());
//     std::reverse(themes.begin(), themes.end());
//     std::reverse(months.begin(), months.end());
// }

std::vector<str::String>
post::Attendance::getAttendance() noexcept
{
    std::vector<str::String> result;

    for (auto& attend : attendance)
    {
        auto& cur = result.emplace_back();
        int cnt   = 1;
        for (auto& flag : {false, true})
        {
            for (auto& i : orderedNames)
            {
                if (i.first[0] == ' ' ^ flag) continue;

                int id           = i.second;
                const char* name = i.first;

                cur += dom::toString(cnt) + "& " + name;
                for (auto& j : attend[id])
                {
                    cur += "& " + j;
                }
                cur += "\\\\ \\hline\n";

                ++cnt;
            }
        }
    }

    return result;
}

std::vector<str::String>
post::Attendance::getLessons() noexcept
{
    return themes;
}

std::vector<str::String>
post::Attendance::getDates() noexcept
{
    return dates;
}

std::vector<str::String>
post::Attendance::getMonths() noexcept
{
    return months;
}

bool
post::Attendance::empty() const noexcept
{
    return attendance.empty();
}
