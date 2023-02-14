#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string_view>
#include <vector>
#include <set>

#include "database/database_query.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace core
{
class PostHandler
{
public:
    template <typename T>
    static crow::json::wvalue process(const crow::request& aReq, data::DatabaseQuery& aDBQ)
    {
        auto req   = crow::json::load(aReq.body);
        auto table = getStructTable<T>(req, aDBQ);
        aDBQ.update<T>(table);
        return {};
    }

    //TODO: remove aDBQ!
    template <typename T>
    static auto getStructTable(const crow::json::rvalue& aReq,
                               data::DatabaseQuery& aDBQ) noexcept
    {
        data::Table<T> result;
        result.emplace_back();
        auto& temp = result.back();
        for (auto& i : aReq)
        {
            auto ind = result.getIndex(i.key());
            if (ind == -1) continue;

            switch (result.types[ind])
            {
                case data::Type::INT:
                    *(int*)temp[ind] = i.i();
                    break;
                case data::Type::BOOL:
                    *(bool*)temp[ind] = i.b();
                    break;
                case data::Type::CHARS:
                    strcpy((char*)temp[ind], i.s().s_);
                    break;
                case data::Type::STRING:
                    *(std::string*)temp[ind] = i.s();
                    break;
            }
        }

        if (T::tableName == "user")
        {
            std::set<std::string> roles;
            for (auto it = aReq["role"].begin(); it != aReq["role"].end(); ++it)
            {
                roles.insert(it->s());
            }

            int num    = 0;
            auto table = aDBQ.getData<data::Role>();
            for (auto& i : table)
            {
                if (roles.count(*(std::string*)i[1]))
                {
                    num += *(int*)i[0];
                }
            }

            *(int*)result[0][result.names["role_id"]] = num;
        }

        return result;
    }

protected:

    static std::string uploadFile(crow::multipart::message& aMsg,
                                  data::DatabaseQuery& aDBQ);
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
