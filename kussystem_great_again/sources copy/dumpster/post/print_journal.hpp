#ifndef PRINT_JOURNAL_HPP
#define PRINT_JOURNAL_HPP

#include <string>

#include "database/database_structures.hpp"

#include "tex_manager/tex_file.hpp"

#include "attendance.hpp"

namespace post
{
class PrintJournal
{
public:
    static str::String process(const char* aData) noexcept;

private:
    static str::String makeJournal(tex::TexFile& aTexFile, int aID) noexcept;
    static Attendance makeAttendance(
        const data::JournalTable& aJournal) noexcept;
    static str::String makeFrontPage(
        const data::JournalTable& aJournal) noexcept;

    static const int limit = 15;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !PRINT_JOURNAL_HPP
