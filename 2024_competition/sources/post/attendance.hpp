#ifndef ATTENDANCE_HPP
#define ATTENDANCE_HPP

#include <cstdint>
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
    void setMark(int aStudentId,
                 int aDateNum,
                 const std::string& aMark) noexcept;

    void newPage(uint8_t aMounth) noexcept;
    void emplaceLesson(uint8_t aDate,
                       const std::string& aTheme,
                       const std::string& aTeacher) noexcept;
    void addFiller() noexcept;

    std::vector<std::string> getAttendance() noexcept;
    std::vector<std::string> getLessons() noexcept;
    std::vector<std::string> getDates() noexcept;
    std::vector<std::string> getMonths() noexcept;

    // void reverse() noexcept;
    bool empty() const noexcept;

private:
    int size;
    uint8_t curMounth;
    std::map<std::string, int> orderedNames;
    std::vector<std::unordered_map<int, std::vector<std::string>>> attendance;
    std::vector<std::string> dates;
    std::vector<std::string> themes;
    std::vector<std::string> months;
};

} // namespace post

//--------------------------------------------------------------------------------

#endif // !ATTENDANCE_HPP
