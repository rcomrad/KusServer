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
    static crow::json::wvalue process(PostRequest<data::Journal_table>& aReq) noexcept;

    static crow::json::wvalue rawDataHandler(data::RawData& aData) noexcept;
    // static void headerParser(data::RawData& aData,
    //                          const crow::multipart::message& msg) noexcept;

private:
    static void makeSchedule(data::Journal_table& aJournal) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_JOURNAL_HANDLER_HPP
