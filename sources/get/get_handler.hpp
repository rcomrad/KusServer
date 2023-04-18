#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <fstream>
#include <unordered_set>

#include "database/connection_manager.hpp"
#include "database/data_request.hpp"

#include "file/path.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace get
{
class GetHandler
{
public:
    static crow::json::wvalue singlGet(const std::string& aRequest,
                                       const std::string& aCondition) noexcept;

    static crow::json::wvalue multiplelGet(
        const std::string& aRequest, const std::string& aCondition) noexcept;

    static crow::json::wvalue mainGet(const std::string& aRequest,
                                      const std::string& aCondition) noexcept;

    template <typename T>
    static crow::json::wvalue process(
        const std::vector<int>& aColumn,
        data::SmartConnection& aConnection) noexcept
    {
        auto table     = aConnection.val.getTable<T>(aColumn);
        auto tableList = getTableAsList(table);
        crow::json::wvalue result;
        result[T::tableName] = std::move(tableList);
        return result;
    }

    template <typename T>
    static std::string dump() noexcept
    {
        auto connection  = data::ConnectionManager::getUserConnection();
        std::string data = getDataAsDMP<T>();

        std::string filePath;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            auto table      = connection.val.getData<data::File>();
            std::string pathPrefix =
                file::Path::getInstance().getPath("dump").value();
            filePath = pathPrefix + std::to_string(table[0].num++) + "-" +
                       T::tableName + ".dmp";
            connection.val.update<data::File>(table);
        }

        std::ofstream out(filePath);
        out << data;
        return filePath;
    }

    template <typename T>
    static std::string getDataAsDMP() noexcept
    {
        data::Table<T> table;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            table           = connection.val.getData<T>();
        }

        // std::vector<int> mx(table[0].columnNames.size(), 0);

        // for (auto& i : table)
        // {
        //     for (int j = 0; j < AsteriskHendler::table[T::tableName].size();
        //          ++j)
        //     {
        //         auto& name = AsteriskHendler::table[T::tableName][j];
        //         auto indx  = table.names[name];
        //         int sz     = 0;
        //         switch (table.types[indx])
        //         {
        //             case data::Type::INT:
        //                 sz = data::wrap(*(int*)i[indx]).size();
        //                 break;
        //             case data::Type::BOOL:
        //                 sz = data::wrap(*(bool*)i[indx]).size();
        //                 break;
        //             case data::Type::CHARS:
        //                 sz = data::wrap(*(char*)i[indx]).size();
        //                 break;
        //             case data::Type::STRING:
        //                 sz = data::wrap(*(std::string*)i[indx]).size();
        //                 break;
        //         }

        //         mx[j] = std::max(mx[indx], sz);
        //         // mn[j] = std::min(mn[indx], sz);
        //     }
        // }

        std::string result = table.getTableName() + "\n";
        for (auto& i : table)
        {
            for (int j = 0; j < AsteriskHendler::table[T::tableName].size();
                 ++j)
            {
                result.push_back('\t');
                auto& name = AsteriskHendler::table[T::tableName][j];
                auto indx  = table.names[name];

                std::string temp;
                switch (table.types[indx])
                {
                    case data::Type::INT:
                        temp = data::wrap(*(int*)i[indx]);
                        break;
                    case data::Type::BOOL:
                        temp = data::wrap(*(bool*)i[indx]);
                        break;
                    case data::Type::CHARS:
                        temp = data::wrap(*(char*)i[indx]);
                        break;
                    case data::Type::STRING:
                        temp = data::wrap(*(std::string*)i[indx]);
                        break;
                }
                result += temp;
                // if (j < AsteriskHendler::table[T::tableName].size() - 1)
                // {
                //     result.push_back(';');
                //     for (int i = 1; i < (mx[j] - temp.size()) / 3; ++i)
                //         result.push_back('\t');
                // }
            }
            result.push_back('\n');
        }
        result += "END\n";

        return result;
    }

protected:
    template <typename T>
    static crow::json::wvalue::list getTableAsList(
        const data::Table<T>& aTable) noexcept
    {
        crow::json::wvalue::list result;

        for (auto& i : aTable)
        {
            crow::json::wvalue temp;
            for (auto& col : aTable.names)
            {
                auto& name = col.first;
                auto indx  = col.second;
                switch (aTable.types[indx])
                {
                    case data::Type::INT:
                        if (*(int*)i[indx] != 0) temp[name] = *(int*)i[indx];
                        break;
                    case data::Type::BOOL:
                        // TODO:
                        temp[name] = *(bool*)i[indx];
                        break;
                    case data::Type::CHARS:
                        temp[name] = std::string((char*)i[indx]);
                        break;
                    case data::Type::STRING:
                        if ((*(std::string*)i[indx])[0] != 0)
                            temp[name] = *(std::string*)i[indx];
                        break;
                }
            }
            result.emplace_back(std::move(temp));
        }

        return result;
    }
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_HANDLER_HPP
