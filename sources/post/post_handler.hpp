#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "database/connection_manager.hpp"

#include "file/file.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace post
{
class PostHandler
{
private:
    template <typename T>
    struct PostRequest
    {
        T data;
        std::unordered_map<std::string, std::vector<int>> manyToMany;
        std::unordered_map<std::string, crow::json::rvalue> other;
    };

public:
    template <typename T>
    static crow::json::wvalue process(const crow::request& aReq)
    {
        auto body    = crow::json::load(aReq.body);
        auto request = parseRequest<T>(body);

        int res;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            res             = connection.val.update<T>(request.data);
        }

        manyToManyTransmiter(request);

        return {res};
    }

    template <typename T>
    static void manyToManyTransmiter(const PostRequest<T>& aReq)
    {
        for (auto& i : aReq.manyToMany)
        {
            transmitToMTMHandler(i.first, aReq.id(), aReq.other.count("add"),
                                 i.second, aReq.data.getTableName());
        }
    }

    template <typename T>
    static crow::json::wvalue manyToMany(int aID,
                                         bool aIsAdding,
                                         std::vector<int> aIDForInsert,
                                         const std::string& aTableName)
    {
        auto connection = data::ConnectionManager::getUserConnection();
        data::DataArray<T> table;
        table.reserve(16);

        auto it = T::nameToNum.find(aTableName + "_id");
        crow::json::wvalue res;
        if (it == T::nameToNum.end())
        {
            res = {"404"};
        }
        else
        {
            int l = it->second;
            int r = l == 1 ? 2 : 1;

            if (!aIsAdding)
            {
                table.emplace_back();
                *(int*)table.back()[l] = aID;
                connection.val.drop<T>(table);
                table.pop_back();
            }

            for (auto i : aIDForInsert)
            {
                table.emplace_back();
                *(int*)table.back()[l] = aID;
                *(int*)table.back()[r] = i;
            }

            res = connection.val.insert<T>(table);
        }

        return {res};
    }

    template <typename T>
    static crow::json::wvalue uploadFromFile(const crow::request& aReq)
    {
        crow::json::wvalue res;

        crow::multipart::message msg(aReq);
        std::string filePath = uploadFile(msg);
        auto data = file::FileRouter::process(filePath);

        for(const auto& i : data)
        {
            data::DataArray
        }

        return {400};
    }

    template <typename T>
    static crow::json::wvalue drop(const crow::request& aReq)
    {
        auto connection = data::ConnectionManager::getUserConnection();
        auto req        = crow::json::load(aReq.body);
        if (req.begin()->t() != crow::json::type::List)
        {
            auto data = parseRequest<T>(req).data;
            connection.val.drop(data);
        }
        else
        {
            std::vector<int> ids;
            for (auto& i : *req.begin()) ids.push_back(i.i());
            connection.val.dropByID<T>(ids);
        }

        return {};
    }

    template <typename T>
    static crow::json::wvalue rawDataInsert(
        const std::vector<std::vector<std::string>>& aData)
    {
        data::DataArray<T> table;
        auto res        = table.loadFromRawData(aData);
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.insert(table);
        return {res};
    }

protected:
    template <typename T>
    static auto parseRequest(const crow::json::rvalue& aReq) noexcept
    {
        PostRequest<T> result;
        result.data.setFromJson(aReq);

        for (auto& i : aReq)
        {
            if (!T::nameToNum.count(i.key()))
            {
                if (i.t() == crow::json::type::List &&
                    i[0].t() == crow::json::type::Number)
                {
                    auto& list = result.manyToMany[i.key()];
                    for (auto& j : i) list.push_back(j.i());
                }
                else
                {
                    result.other[i.key()] = i;
                }
                continue;
            }
        }

        return result;
    }

    static std::string uploadFile(crow::multipart::message& aMsg,
                                  std::string aPathPrefix = "");

private:
    static void transmitToMTMHandler(const std::string aTableName,
                                     int aID,
                                     bool aIsAdding,
                                     std::vector<int> aIDForInsert,
                                     const std::string aTrueNam);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
