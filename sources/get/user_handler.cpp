#include "user_handler.hpp"

crow::json::wvalue
get::UserHandler::process(const std::vector<int>& aColumn,
                          data::DatabaseQuery& aDBQ) noexcept
{
    auto table     = aDBQ.select2<data::User>(aColumn);
    auto tableList = getTableAsList(table);

    if (table.size() > 0 && table[0].role_id != 0)
    {
        for (int num = 0; num < table.size(); ++num)
        {
            crow::json::wvalue::list roleList;
            int role = table[num].role_id;
            for (int i = 0; i < mRoles.size(); ++i, role >>= 1)
            {
                if (role & 1)
                {
                    roleList.emplace_back(mRoles[i]);
                }
            }
            tableList[num]["role"] = std::move(roleList);
        }
    }

    crow::json::wvalue result;
    result["user"] = std::move(tableList);
    return result;
}

std::vector<std::string> get::UserHandler::mRoles = getAllRoles();

std::vector<std::string>
get::UserHandler::getAllRoles() noexcept
{
    std::vector<std::string> result;
    data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
    auto table = dbq.getData<data::Role>();
    result.reserve(table.size());
    for (auto& rol : table)
    {
        result.emplace_back(std::move(rol.name));
    }
    return result;
}
