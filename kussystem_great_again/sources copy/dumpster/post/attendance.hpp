#ifndef ATTENDANCE_HPP
#define ATTENDANCE_HPP

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace post
{
class Attendance
{
public:
    Attendance(int aID, int aSize) noexcept;
    void setMark(int aStudentId, int aDateNum, const char* aMark) noexcept;

    void newPage(uint8_t aMounth) noexcept;
    void emplaceLesson(uint8_t aDate,
                       const char* aTheme,
                       const char* aTeacher) noexcept;
    void addFiller() noexcept;

    std::vector<str::String> getAttendance() noexcept;
    std::vector<str::String> getLessons() noexcept;
    std::vector<str::String> getDates() noexcept;
    std::vector<str::String> getMonths() noexcept;

    // void reverse() noexcept;
    bool empty() const noexcept;

private:
    int size;
    uint8_t curMounth;
    std::map<str::String, int> orderedNames;
    std::vector<std::unordered_map<int, std::vector<str::String>>> attendance;
    std::vector<str::String> dates;
    std::vector<str::String> themes;
    std::vector<str::String> months;
};

} // namespace post

//--------------------------------------------------------------------------------

#endif // !ATTENDANCE_HPP
