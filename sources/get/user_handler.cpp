#include "user_handler.hpp"

#include "core/role.hpp"

crow::json::wvalue
get::UserHandler::process(const std::unordered_set<std::string>& aColumn,
                          data::SmartConnection& aConnection) noexcept
{
    auto table = aConnection.val.select2<data::User>(aColumn);
    table.turnOffColumn("role_id");
    auto tableList = getTableAsList(table);

    if (table.size() > 0 && table[0].role_id != 0)
    {
        for (int num = 0; num < table.size(); ++num)
        {
            auto roles = core::Role::getInstance().getRoles(table[num].role_id);
            crow::json::wvalue::list roleList;
            for (auto& i : roles)
            {
                roleList.emplace_back(i);
            }
            tableList[num]["role"] = std::move(roleList);
        }
    }

    crow::json::wvalue result;
    result["user"] = std::move(tableList);
    return result;
}
