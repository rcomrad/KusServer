#ifndef JOURNAL_HANDLER_HPP
#define JOURNAL_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string_view>
#include <vector>

#include "database/database_query.hpp"

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class JournalHandler : protected PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq, data::DatabaseQuery& aDBQ);
    static void loadFromFile(std::string_view aFileName, data::DatabaseQuery& aDBQ);

private:
    static void make(data::Table<data::Journal_table>& aJournal,
              std::vector<int> aSchedule, data::DatabaseQuery& aDBQ);

    static void makeSchedule(data::Table<data::Journal_table>& aJournal,
                      std::vector<int> aSchedule, data::DatabaseQuery& aDBQ);
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !JOURNAL_HANDLER_HPP
