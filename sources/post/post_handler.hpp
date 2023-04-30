#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "database/connection_manager.hpp"

#include "file/file.hpp"
#include "file/file_router.hpp"

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
    static crow::json::wvalue process(const crow::request& aReq) noexcept
    {
        auto body    = crow::json::load(aReq.body);
        auto request = parseRequest<T>(body);

        int res;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            res             = connection.val.write<T>(request.data);
        }

        manyToManyTransmiter(request);

        return {res};
    }

    template <typename T>
    static void manyToManyTransmiter(const PostRequest<T>& aReq) noexcept
    {
        for (auto& i : aReq.manyToMany)
        {
            transmitToMTMHandler(i.first, aReq.data.id, aReq.other.count("add"),
                                 i.second, T::tableName);
        }
    }

    template <typename T>
    static crow::json::wvalue manyToMany(int aID,
                                         bool aIsAdding,
                                         std::vector<int> aIDForInsert,
                                         const std::string& aTableName) noexcept
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
    static crow::json::wvalue drop(const crow::request& aReq) noexcept
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

    //--------------------------------------------------------------------------------

    static crow::json::wvalue uploadFromFile(
        const std::string aType, const std::string aFileName) noexcept;
    static crow::json::wvalue uploadFromFileRequest(
        const std::string aType, const crow::request& aReq) noexcept;

    template <typename T>
    static crow::json::wvalue rawDataHandler(
        std::vector<std::vector<std::string>>& aData,
        const std::vector<std::vector<std::string>>& aAdditionalInfo =
            {}) noexcept
    {
        return rawDataInsert<T>(aData);
    }

    template <typename T>
    static crow::json::wvalue rawDataInsert(
        const std::vector<std::vector<std::string>>& aData) noexcept
    {
        data::DataArray<T> table;
        auto res        = table.loadFromRawData(aData);
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.insert(table);
        return {res};
    }

    //--------------------------------------------------------------------------------

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
                                  std::string aPathPrefix = "") noexcept;

private:
    static void transmitToMTMHandler(const std::string aTableName,
                                     int aID,
                                     bool aIsAdding,
                                     std::vector<int> aIDForInsert,
                                     const std::string aTrueNam) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
