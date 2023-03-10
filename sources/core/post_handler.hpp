#ifndef POST_HANDLER_BASE_HPP
#define POST_HANDLER_BASE_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "domain/pair.hpp"

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
        auto req = crow::json::load(aReq.body);

        std::unordered_map<std::string, crow::json::rvalue> manyToMany;
        auto table = getStructTable<T>(req, aDBQ, &manyToMany);
        auto res   = aDBQ.update<T>(table);

        bool add = manyToMany.count("add");
        for (auto& i : manyToMany)
        {
            transmitToPostHandler(i.first, res, i.second, aDBQ, add);
        }

        return {res};
    }

    template <typename T>
    static crow::json::wvalue supportingProcess(int aID,
                                                crow::json::rvalue& aPartnerIDs,
                                                data::DatabaseQuery& aDBQ,
                                                bool aIsAdding)
    {
        data::Table<T> table;
        // table.reserve(30);
        if (!aIsAdding)
        {
            table.emplace_back();
            *(int*)table.back()[1] = aID;
            aDBQ.drop<T>(table);
            table.pop_back();
        }
        for (auto& i : aPartnerIDs)
        {
            table.emplace_back();
            *(int*)table.back()[1] = aID;
            *(int*)table.back()[2] = i.i();
        }
        auto res = aDBQ.update<T>(table);
        return {res};
    }

    template <typename T>
    static crow::json::wvalue loadFromFile(const crow::request& aReq,
                                           data::DatabaseQuery& aDBQ)
    {
        crow::multipart::message msg(aReq);
        std::string filePath = uploadFile(msg, aDBQ);

        return {200};
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
    static auto getStructTable(
        const crow::json::rvalue& aReq, data::DatabaseQuery& aDBQ,
        std::unordered_map<std::string, crow::json::rvalue>* aManyToMany =
            nullptr) noexcept
    {
        data::Table<T> result(1);
        auto& temp = result.back();

        for (auto& i : aReq)
        {
            auto ind = result.getIndex(i.key());
            if (ind == -1)
            {
                if (aManyToMany != nullptr)
                {
                    (*aManyToMany)[i.key()] = i;
                }
                continue;
            }

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

private:
    static void transmitToPostHandler(const std::string& aTableName, int aID,
                                      crow::json::rvalue& aPartnerIDs,
                                      data::DatabaseQuery& aDBQ,
                                      bool aIsAdding);
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_BASE_HPP
