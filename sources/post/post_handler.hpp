#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "database/connection_manager.hpp"
#include "database/raw_data.hpp"

#include "file/file.hpp"
#include "file/file_router.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace post
{

enum class ManyToMany
{
    NUN,
    ADD,
    REPLACE
};

template <typename T>
struct PostRequest
{
    T data;
    ManyToMany type;
    std::unordered_map<std::string, crow::json::rvalue> leftovers;
};

class PostHandler
{

public:
    // template <typename HandlerType, typename TableType>
    // static crow::json::wvalue basicPost(const crow::request& aReq) noexcept
    // {
    //     auto body    = crow::json::load(aReq.body);
    //     auto request = parseRequest<TableType>(body);

    //     crow::json::wvalue res;
    //     res = HandlerType::process(request);

    //     if (request.type != ManyToMany::NUN)
    //     {
    //         manyToMany(request.data.id, request.data.geName(), request.type,
    //                    request.leftovers);
    //     }

    //     return res;
    // }

    // template <typename T>
    // static crow::json::wvalue process(PostRequest<T>& aReq) noexcept
    // {
    //     int res;
    //     auto connection = data::ConnectionManager::getUserConnection();
    //     res             = connection.val.write(aReq.data);
    //     return {res};
    // }

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

    // template <typename T>
    // static crow::json::wvalue process(data::DataArray<T>& aTable) noexcept
    // {
    //     std::vector<char> tableFlag(T::types.size(), -1);
    //     for (size_t i = 3; i < T::types.size(); ++i)
    //     {
    //         std::string temp = T::names[j];
    //         temp.resize(T::names[1].size() - 3);
    //         temp += "_id"s;
    //         tableFlag[i] = temp == T::names[1] ? 1 : ;
    //     }

    //     for (auto& i : aTable)
    //     {
    //     }

    //     auto connection = data::ConnectionManager::getUserConnection();
    //     res             = connection.val.insert(request.data);

    //     return {res};
    // }

    // template <typename T>
    // static void manyToManyTransmiter(const PostRequest<T>& aReq) noexcept
    // {
    //     for (auto& i : aReq.manyToMany)
    //     {
    //         transmitToMTMHandler(i.first, aReq.data.id,
    //         aReq.other.count("add"),
    //                              i.second, T::tableName);
    //     }
    // }

    // template <typename T>
    // static crow::json::wvalue manyToMany(const PostRequest<T>& aReq) noexcept
    // {
    //     for (auto& other : aReq.leftovers)
    //     {
    //         data::RawData aData;
    //         // header;
    //         auto& value = aData.value;
    //     }

    //     auto it = T::nameToNum.find(aTableName + "_id"s);
    //     crow::json::wvalue res;

    //     data::DataArray<T> table;
    //     if (request.type == PostRequest::ManyToMany::REPLACE)
    //     {
    //         auto connection = data::ConnectionManager::getUserConnection();
    //         connection.val.drop(request.data);
    //         table = connection.val.getDataArray(request.data);
    //     }

    //     int l = it->second;
    //     int r = l == 1 ? 2 : 1;

    //     for (auto i : aIDForInsert)
    //     {
    //         table.emplace_back();
    //         *(int*)table.back()[l] = aID;
    //         *(int*)table.back()[r] = i;
    //     }

    //     res = connection.val.insert<T>(table);

    //     return res;
    // }

    // template <typename T>
    // static crow::json::wvalue manyToMany(int aID,
    //                                      bool aIsAdding,
    //                                      std::vector<int> aIDForInsert,
    //                                      const std::string& aTableName)
    //                                      noexcept
    // {
    //     auto connection = data::ConnectionManager::getUserConnection();
    //     data::DataArray<T> table;
    //     table.reserve(16);

    //     auto it = T::nameToNum.find(aTableName + "_id");
    //     crow::json::wvalue res;
    //     if (it == T::nameToNum.end())
    //     {
    //         res = {"404"};
    //     }
    //     else
    //     {
    //         int l = it->second;
    //         int r = l == 1 ? 2 : 1;

    //         if (!aIsAdding)
    //         {
    //             table.emplace_back();
    //             *(int*)table.back()[l] = aID;
    //             connection.val.drop<T>(table);
    //             table.pop_back();
    //         }

    //         for (auto i : aIDForInsert)
    //         {
    //             table.emplace_back();
    //             *(int*)table.back()[l] = aID;
    //             *(int*)table.back()[r] = i;
    //         }

    //         res = connection.val.insert<T>(table);
    //     }

    //     return {res};
    // }

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
        std::unordered_map<std::string, std::string>&& aHeader,
        const std::string& aFileName) noexcept;
    static crow::json::wvalue uploadFromFileRequest(
        const std::string& aType, const crow::request& aReq) noexcept;

    template <typename T>
    static crow::json::wvalue rawDataHandler(data::RawData& aData) noexcept
    {
        auto it = aData.header.find("partly");
        if (it != aData.header.end() && it->second == "true" &&
            T::types.size() > 3)
        {
            std::string first = T::columnNames[1];
            first.resize(first.size() - 3);
            std::string second = T::columnNames[2];
            second.resize(second.size() - 3);

            for (size_t i = 3; i < T::types.size(); ++i)
            {
                std::string temp = T::columnNames[i];
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
        const std::vector<std::vector<std::string>>& aData) noexcept
    {
        // TODO: result
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
        result.type = ManyToMany::NUN;
        result.data.setFromJson(aReq);

        for (auto& i : aReq)
        {
            if (i.key() == "many_to_many"s)
            {
                if (i.s() == "add")
                {
                    result.type = ManyToMany::ADD;
                }
                else if (i.s() == "replace")
                {
                    result.type = ManyToMany::REPLACE;
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

    static std::string uploadFile(crow::multipart::message& aMsg,
                                  std::string aPathPrefix = "") noexcept;

    // private:
    //     static void transmitToMTMHandler(const std::string aTableName,
    //                                      int aID,
    //                                      bool aIsAdding,
    //                                      std::vector<int> aIDForInsert,
    //                                      const std::string aTrueNam)
    //                                      noexcept;

private:
    static crow::json::wvalue manyToMany(
        int aID,
        const std::string& aTableName,
        ManyToMany& aType,
        std::unordered_map<std::string, crow::json::rvalue>
            aLeftovers) noexcept;

    static void setRawData(std::vector<std::vector<std::string>>& aData,
                           int aNum,
                           const std::string& aTableName,
                           const std::string& aColumnName) noexcept;
};

} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
