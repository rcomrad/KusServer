#ifndef POST_JOURNAL_HANDLER_HPP
#define POST_JOURNAL_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/database_structures.hpp"

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class JournalHandler : protected PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq) noexcept;

    static crow::json::wvalue rawDataHandler(
        std::vector<std::vector<std::string>>& aData,
        const std::vector<std::vector<std::string>>& aAdditionalInfo =
            {}) noexcept;

private:
    static void makeSchedule(data::Journal_table& aJournal) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_JOURNAL_HANDLER_HPP
