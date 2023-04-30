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
                                       std::string&& aCondition) noexcept;

    static crow::json::wvalue multiplelGet(const std::string& aRequest,
                                           std::string&& aCondition) noexcept;

    static crow::json::wvalue mainGet(const std::string& aRequest,
                                      std::string&& aCondition) noexcept;

    template <typename T>
    static crow::json::wvalue process(
        const std::unordered_set<std::string>& aColumn,
        data::SmartConnection& aConnection) noexcept
    {
        auto table = aConnection.val.getNextDataArray<T>(aColumn);
        crow::json::wvalue result;
        result[T::tableName] = std::move(table.getAsJList());
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
            filePath = pathPrefix + std::to_string(table.num++) + "-" +
                       T::tableName + ".dmp";
            connection.val.update(table);
        }

        std::ofstream out(filePath);
        out << data;
        return filePath;
    }

    template <typename T>
    static std::string getDataAsDMP() noexcept
    {
        data::DataArray<T> table;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            table           = connection.val.getData<T>();
        }

        std::string result = table.getTableName() + "\n";
        for (auto& i : table)
        {
            result += i.getAsDMP();
            result.push_back('\n');
        }
        result += "END\n";

        return result;
    }
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_HANDLER_HPP
