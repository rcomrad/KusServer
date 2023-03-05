#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <vector>

#include "database/database_query.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace core
{
class PostHandler
{
public:
    template <typename T>
    static crow::json::wvalue process(const crow::request& aReq,
                                      data::DatabaseQuery& aDBQ)
    {
        auto req   = crow::json::load(aReq.body);
        auto table = getStructTable<T>(req, aDBQ);
        auto res   = aDBQ.update<T>(table);
        return {res};
    }

    template <typename T>
    static crow::json::wvalue drop(const crow::request& aReq,
                                   data::DatabaseQuery& aDBQ)
    {
        auto req  = crow::json::load(aReq.body);
        auto temp = req.keys();
        for (auto i : temp) std::cout << i << "\n";
        auto table = getStructTable<T>(req, aDBQ);
        aDBQ.drop<T>(table);
        return {};
    }

    // TODO: remove aDBQ!
    template <typename T>
    static auto getStructTable(const crow::json::rvalue& aReq,
                               data::DatabaseQuery& aDBQ) noexcept
    {
        data::Table<T> result;

        if (aReq.begin()->t() != crow::json::type::List)
        {
            getStructTableSup<T>(&aReq, result, aDBQ);
        }
        else
        {
            for (crow::json::rvalue& i : *aReq.begin())
            {
                getStructTableSup<T>(&i, result, aDBQ);
            }
        }

        return result;
    }

    static std::string uploadFile(crow::multipart::message& aMsg,
                                  data::DatabaseQuery& aDBQ,
                                  std::string aPathPrefix = "");

private:
    // TODO: remove aDBQ!
    template <typename T>
    static void getStructTableSup(const crow::json::rvalue* aReq,
                                  data::Table<T>& result,
                                  data::DatabaseQuery& aDBQ) noexcept
    {
        result.emplace_back();
        auto& temp = result.back();
        for (auto& i : *aReq)
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

        if (T::tableName == "user" && aReq->has("role"))
        {
            std::set<std::string> roles;
            for (auto it = (*aReq)["role"].begin(); it != (*aReq)["role"].end();
                 ++it)
            {
                roles.insert(it->s());
            }

            int num    = 0;
            auto table = aDBQ.getData<data::Role>();
            for (auto& i : table)
            {
                if (roles.count(*(std::string*)i[1]))
                {
                    num += 1 << (*(int*)i[0] - 1);
                }
            }

            *(int*)result.back()[result.names["role_id"]] = num;
        }
    }
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
