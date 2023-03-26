#include "user_handler.hpp"

crow::json::wvalue
get::UserHandler::process(const std::vector<int>& aColumn,
                          data::DatabaseQuery& aDBQ) noexcept
{
    auto tableList = getTableAsList<data::User>(aColumn, aDBQ);
    crow::json::wvalue result;
    result["user"] = std::move(tableList);
    // result[data::User::tableName] = std::move(tableList);

    // if ()
    // {
    // }
    // data::DatabaseQuery dbq(mDBS);
    // auto table  = dbq.getData<data::Role>();
    // int nameNum = table.names["name"];
    // for (auto& i : table)
    // {
    //     roles.emplace_back(*(std::string*)i[nameNum]);
    // }

    // auto it = aCondition.end();
    // while (*(--it) != ' ')
    //     ;
    // std::string temp(it, aCondition.end());
    // // std::cout << temp << "\n";
    // int rol = std::stoi(temp);

    // for (int i = 0; rol; ++i)
    // {
    //     if (rol & 1)
    //     {
    //         res.emplace_back(roles[i]);
    //     }

    //     rol >>= 1;
    // }

    return result;
}