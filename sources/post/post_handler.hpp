#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "domain/pair.hpp"

#include "database/connection_manager.hpp"

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
        data::Table<T> table;
        std::unordered_map<std::string, std::vector<int>> manyToMany;
        std::unordered_map<std::string, crow::json::rvalue> other;

        PostRequest() : table(1)
        {
        }

        int id() const
        {
            return table[0].id;
        }
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
            res             = connection.val.update<T>(request.table);
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
                                 i.second, aReq.table.getTableName());
        }
    }

    template <typename T>
    static crow::json::wvalue manyToMany(int aID,
                                         bool aIsAdding,
                                         std::vector<int> aIDForInsert,
                                         const std::string& aTableName)
    {
        auto connection = data::ConnectionManager::getUserConnection();
        data::Table<T> table;
        table.reserve(16);

        auto ss  = aTableName + "_id";
        auto sss = table.names;

        auto it = table.names.find(aTableName + "_id");
        crow::json::wvalue res;
        if (it == table.names.end())
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

            res = connection.val.update<T>(table);
        }

        return {res};
    }

    template <typename T>
    static crow::json::wvalue uploadFromFile(const crow::request& aReq)
    {
        // crow::multipart::message msg(aReq);
        // std::string filePath = uploadFile(msg, aDBQ);

        return {400};
    }

    template <typename T>
    static crow::json::wvalue drop(const crow::request& aReq)
    {
        auto connection = data::ConnectionManager::getUserConnection();
        auto req        = crow::json::load(aReq.body);
        if (req.begin()->t() != crow::json::type::List)
        {
            auto table = parseRequest<T>(req).table;
            connection.val.drop<T>(table);
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
    struct DataFile
    {
        data::Table<T> table;
        std::vector<std::vector<std::string>> additionalLines;
    };

    template <typename T>
    static auto dataFileParser(const std::string& aFilePath,
                               int aAdditionalLineCount     = 0,
                               std::set<int> aErasedIndexes = {0})
    {
        DataFile<T> result;
        std::ifstream inp(aFilePath);

        std::string firstString;
        std::getline(inp, firstString);

        std::string s;
        while (std::getline(inp, s))
        {
            result.table.emplace_back();
            auto& temp = result.table.back();

            std::stringstream ss;
            ss << s;
            for (int ind = 0; ind < result.table.types.size(); ++ind)
            {
                if (aErasedIndexes.count(ind)) continue;

                switch (result.table.types[ind])
                {
                    case data::Type::INT:
                        ss >> *(int*)temp[ind];
                        break;
                    case data::Type::BOOL:
                        ss >> *(bool*)temp[ind];
                        break;
                    // case data::Type::CHARS:
                    //     strcpy((char*)temp[ind], i.s().s_);
                    //     break;
                    case data::Type::STRING:
                        ss >> *(std::string*)temp[ind];
                        break;
                }
            }

            if (aAdditionalLineCount)
            {
                std::string additionalLine;

                result.additionalLines.emplace_back();
                for (int i = 0; i < aAdditionalLineCount; ++i)
                {
                    std::getline(inp, additionalLine);
                    result.additionalLines.back().emplace_back(additionalLine);
                }
            }
        }

        return result;
    }

protected:
    template <typename T>
    static auto parseRequest(const crow::json::rvalue& aReq) noexcept
    {
        PostRequest<T> result;
        auto& temp  = result.table.back();
        auto& table = result.table;

        for (auto& i : aReq)
        {
            auto ind = table.getIndex(i.key());
            if (ind == -1)
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

            switch (table.types[ind])
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
