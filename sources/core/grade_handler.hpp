#ifndef GRADE_HANDLER_HPP
#define GRADE_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string_view>

#include "database/database_query.hpp"

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class GradeHandler : protected PostHandler
{
public:
    template <typename T1, typename T2>
    static crow::json::wvalue process(const crow::request& aReq, data::DatabaseQuery& aDBQ)
    {
        auto req              = crow::json::load(req.body);
        data::Table<T1> table = getStruct<T1>(req, aDBQ);
        aDBQ.update<T1>(table);

        data::Table<T2> students;
        for (auto it = req["students"].begin(); it != req["students"].end();
             ++it)
        {
            students.emplace_back();
            students.back().student_id = it->i();
            students.back().grade_id   = table[0].id;
        }
        aDBQ.update<T2>(students);

        return {};
    }
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !GRADE_HANDLER_HPP
