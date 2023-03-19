#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/data_request.hpp"
#include "database/database_query.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace get
{
class GetHandler
{
public:
    static crow::json::wvalue mainGet(const std::string& aRequest,
                                      const std::string& aCondition,
                                      data::DBSettings& aDBS) noexcept;

    template <typename T>
    static crow::json::wvalue process(const std::vector<int>& aColumn,
                                      data::DatabaseQuery& aDBQ) noexcept
    {
        auto table = aDBQ.select2<T>(aColumn);
        crow::json::wvalue::list tableList;

        for (auto& i : table)
        {
            crow::json::wvalue temp;
            for (auto& col : table.names)
            {
                auto& name = col.first;
                auto indx  = col.second;
                switch (table.types[indx])
                {
                    case data::Type::INT:
                        temp[name] = *(int*)i[indx];
                        break;
                    case data::Type::BOOL:
                        temp[name] = *(bool*)i[indx];
                        break;
                    case data::Type::CHARS:
                        temp[name] = std::string((char*)i[indx]);
                        break;
                    case data::Type::STRING:
                        temp[name] = *(std::string*)i[indx];
                        break;
                }
            }
            tableList.emplace_back(std::move(temp));
        }

        crow::json::wvalue result;

        if (tableList.size() == 1)
        {
            result["a"] = std::move(result[0]);
        }
        else
        {
            result["a"] = std::move(result);
        }

        return result;
    }
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_HANDLER_HPP
