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
    static crow::json::wvalue process(const crow::request& aReq);
    static crow::json::wvalue uploadFromFile(const crow::request& aReq);
    static crow::json::wvalue dataFileUpload(const std::string& aFilePath);

private:
    static void makeSchedule(data::Journal_table& aJournal);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_JOURNAL_HANDLER_HPP
