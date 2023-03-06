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
        auto req = crow::json::load(aReq.body);
        if (req.begin()->t() != crow::json::type::List)
        {
            auto table = getStructTable<T>(req, aDBQ);
            aDBQ.drop<T>(table);
        }
        else
        {
            for (crow::json::rvalue& i : *req.begin())
            {
                auto IDs = getIDs(req);
                aDBQ.dropByID<T>(IDs);
            }
        }

        return {};
    }

    static std::vector<int> getIDs(const crow::json::rvalue& aReq) noexcept
    {
        std::vector<int> res;
        for (auto& i : *aReq.begin()) res.push_back(i.i());
        return res;
    }

    // TODO: remove aDBQ!
    template <typename T>
    static auto getStructTable(const crow::json::rvalue& aReq,
                               data::DatabaseQuery& aDBQ) noexcept
    {
        data::Table<T> result(1);
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

        if (T::tableName == "user" && aReq.has("role"))
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
                    num += 1 << (*(int*)i[0] - 1);
                }
            }

            *(int*)temp[result.names["role_id"]] = num;
        }

        return result;
    }

    static std::string uploadFile(crow::multipart::message& aMsg,
                                  data::DatabaseQuery& aDBQ,
                                  std::string aPathPrefix = "");
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
