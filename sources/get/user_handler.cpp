#include "user_handler.hpp"

#include "core/role.hpp"

crow::json::wvalue
get::UserHandler::process(const crow::request& aRequest,
                          const std::unordered_set<int>& aColumn,
                          data::SmartConnection& aConnection) noexcept
{
    auto table     = aConnection.val.getNextDataArray<data::User>(aColumn);
    auto tableList = table.getAsJList({"role_id"});

    if (table.size() > 0 && table[0].roleID != 0)
    {
        for (int num = 0; num < table.size(); ++num)
        {
            auto roles = core::Role::getInstance().getRoles(table[num].roleID);
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
