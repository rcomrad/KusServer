#ifndef POST_HANDLER_HPP
#define POST_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "domain/pair.hpp"

#include "database/database_query.hpp"

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
        data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
        auto body = crow::json::load(aReq.body);

        auto request = parseRequest<T>(body);
        auto res     = dbq.update<T>(request.table);

        for (auto& i : request.manyToMany)
        {
            transmitToMTMHandler(i.first, res, request.other.count("add"),
                                 i.second);
        }

        return {res};
    }

    template <typename T>
    static crow::json::wvalue manyToMany(int aID,
                                         bool aIsAdding,
                                         std::vector<int> aIDForInsert)
    {
        data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
        data::Table<T> table;
        table.reserve(16);

        if (!aIsAdding)
        {
            table.emplace_back();
            *(int*)table.back()[1] = aID;
            dbq.drop<T>(table);
            table.pop_back();
        }

        for (auto i : aIDForInsert)
        {
            table.emplace_back();
            *(int*)table.back()[1] = aID;
            *(int*)table.back()[2] = i;
        }
        auto res = dbq.update<T>(table);
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
        data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
        auto req = crow::json::load(aReq.body);
        if (req.begin()->t() != crow::json::type::List)
        {
            auto table = parseRequest<T>(req).table;
            dbq.drop<T>(table);
        }
        else
        {
            std::vector<int> ids;
            for (auto& i : *req.begin()) ids.push_back(i.i());
            dbq.dropByID<T>(ids);
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

    // TODO: remove public!
public:
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
                                     std::vector<int> aIDForInsert);
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_HANDLER_HPP
