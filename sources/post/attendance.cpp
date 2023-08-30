#include "attendance.hpp"

#include <algorithm>

#include "database/connection_manager.hpp"
#include "database/database_structures.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

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

    static auto journalDate = file::File::getAllData(
        file::Path::getPathUnsafe("resource", "attendance.tex"), true);
    std::string result = journalDate;

    std::string attStr;
    int cnt = 1;
    for (auto& flag : {false, true})
    {
        for (auto& i : orderedNames)
        {
            if (i.first[0] == ' ' ^ flag) continue;

            int id                  = i.second;
            const std::string& name = i.first;

            attStr += std::to_string(cnt);
            attStr += "&";
            attStr += name;
            for (auto& j : attendance.back()[id])
            {
                attStr += "&" + j;
            }
            attStr += "\n\\\\ \\hline\n";
            ++cnt;
        }
    }
    attendance.pop_back();

    auto numA    = result.find('A');
    result[numA] = ' ';
    result.insert(numA, attStr);

    auto numD    = result.find('D');
    result[numD] = ' ';
    result.insert(numD, dates.back());
    dates.pop_back();

    auto numM    = result.find('M');
    result[numM] = ' ';
    result.insert(numM, monthNums[months.back()]);
    months.pop_back();

    result += "\\clearpage\n";

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
