#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <fstream>
#include <unordered_set>

#include "database/connection_manager.hpp"

#include "file_data/path.hpp"

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
        const std::unordered_set<int>& aColumn,
        data::SmartConnection& aConnection) noexcept
    {
        auto table = aConnection.val.getNextDataArray<T>(aColumn);
        crow::json::wvalue result;
        result[T::tableName] = std::move(table.getAsJList());
        return result;
    }

    // TODO: better switch
    template <typename T>
    static std::string dump() noexcept
    {
        auto connection = data::ConnectionManager::getUserConnection();
        return getDataAsDMP<T>();
    }

    template <typename T>
    static std::string getDataAsDMP() noexcept
    {
        data::DataArray<T> table;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            table           = connection.val.getDataArray<T>();
        }

        std::string result = table.getTableName() + "\n";
        for (auto& i : table)
        {
            result.push_back('\t');
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
