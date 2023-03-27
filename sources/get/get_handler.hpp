#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <unordered_set>

#include "database/data_request.hpp"
#include "database/database_query.hpp"

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
    static crow::json::wvalue process(const std::vector<int>& aColumn,
                                      data::DatabaseQuery& aDBQ) noexcept
    {
        auto table     = aDBQ.select2<T>(aColumn);
        auto tableList = getTableAsList(table);
        crow::json::wvalue result;
        result[T::tableName] = std::move(tableList);
        return result;
    }

protected:
    template <typename T>
    static crow::json::wvalue::list getTableAsList(const data::Table<T>& aTable) noexcept
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
