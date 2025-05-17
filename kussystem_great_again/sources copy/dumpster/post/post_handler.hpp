#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "database/connection_manager.hpp"
#include "database/raw_data.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace post
{

enum class ManyToMany
{
    NUN     = 0,
    Add     = 1,
    Delete  = 2,
    Replace = 3
};

template <typename T>
struct PostRequest
{
    T data;
    ManyToMany type;
    std::unordered_map<str::String, crow::json::rvalue> leftovers;
};

class PostHandler
{

public:
    template <typename HandlerType, typename TableType>
    static crow::json::wvalue postSubrouter(const crow::request& aReq) noexcept
    {
        auto body    = crow::json::load(aReq.body);
        auto request = parseRequest<TableType>(body);

        crow::json::wvalue res;
        res = HandlerType::process(request);

        if (request.type != ManyToMany::NUN)
        {
            manyToMany(request.data.id, request.data.geName(), request.type,
                       request.leftovers);
        }

        return res;
    }

    template <typename T>
    static crow::json::wvalue process(PostRequest<T>& aReq) noexcept
    {
        int res;
        auto connection = data::ConnectionManager::getUserConnection();
        res             = connection.val.write(aReq.data);
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
            connection.val.dropByID(T::tableName, ids);
        }

        return {};
    }

    //--------------------------------------------------------------------------------

    static crow::json::wvalue uploadFromFile(
        std::unordered_map<str::String, str::String>&& aHeader,
        const char* aFileName) noexcept;
    static crow::json::wvalue uploadFromFileRequest(
        const char* aType,
        const crow::request& aReq) noexcept;

    template <typename T>
    static crow::json::wvalue rawDataHandler(data::RawData& aData) noexcept
    {
        auto it = aData.header.find("partly");
        if (it != aData.header.end() && it->second == "true" &&
            T::types.size() > 3)
        {
            str::String first = T::columnNames[1];
            first.resize(first.size() - 3);
            str::String second = T::columnNames[2];
            second.resize(second.size() - 3);

            for (size_t i = 3; i < T::types.size(); ++i)
            {
                str::String temp = T::columnNames[i];
                first.resize(first.size());

                if (temp == first)
                {
                    setRawData(aData.value, 0, first, T::columnNames[i]);
                }
                else
                {
                    setRawData(aData.value, 1, second, T::columnNames[i]);
                }
            }
        }
        return rawDataInsert<T>(aData.value);
    }

    template <typename T>
    static crow::json::wvalue rawDataInsert(
        const std::vector<std::vector<str::String>>& aData) noexcept
    {
        // TODO: result
        data::DataArray<T> table;
        auto res        = table.loadFromRawData(aData);
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.insert(table);
        return {res};
    }

    //--------------------------------------------------------------------------------

    static str::String uploadFile(
        crow::multipart::message& aMsg,
        const char* aFileKey     = "file",
        const char* aFilenameKey = "filename") noexcept;

protected:
    template <typename T>
    static auto parseRequest(const crow::json::rvalue& aReq) noexcept
    {
        PostRequest<T> result;
        result.type = ManyToMany::NUN;
        result.data.setFromJson(aReq);

        for (auto& i : aReq)
        {
            if (i.key() == "many_to_many"s)
            {
                if (i.s() == "add")
                {
                    result.type = ManyToMany::Add;
                }
                else if (i.s() == "delete")
                {
                    result.type = ManyToMany::Delete;
                }
                else if (i.s() == "replace")
                {
                    result.type = ManyToMany::Replace;
                }
                continue;
            }
            if (!T::nameToNum.count(i.key()))
            {
                result.leftovers[i.key()] = i;
            }
        }
        return result;
    }

private:
    static crow::json::wvalue manyToMany(
        int aID,
        const char* aTableName,
        ManyToMany& aType,
        std::unordered_map<str::String, crow::json::rvalue>
            aLeftovers) noexcept;

    static void setRawData(std::vector<std::vector<str::String>>& aData,
                           int aNum,
                           const char* aTableName,
                           const char* aColumnName) noexcept;
};

} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
