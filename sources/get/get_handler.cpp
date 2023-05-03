#include "get_handler.hpp"

#include <ranges>

#include "get_router.hpp"

crow::json::wvalue
get::GetHandler::singlGet(const std::string& aRequest,
                          std::string&& aCondition) noexcept
{
    crow::json::wvalue result;

    auto temp = mainGet(aRequest, std::move(aCondition));
    auto keys = temp.keys();
    if (keys.size() > 0 && temp[keys[0]].size() > 0)
    {
        result[keys[0]] = std::move(temp[keys[0]][0]);
    }

    return result;
}

crow::json::wvalue
get::GetHandler::multiplelGet(const std::string& aRequest,
                              std::string&& aCondition) noexcept
{
    crow::json::wvalue result = {401};

    auto temp = mainGet(aRequest, std::move(aCondition));
    auto keys = temp.keys();
    if (keys.size() > 0)
    {
        result[keys[0] + "s"] = std::move(temp[keys[0]]);
    }

    return result;
}

crow::json::wvalue
get::GetHandler::mainGet(const std::string& aRequest,
                         std::string&& aCondition) noexcept
{
    crow::json::wvalue result;

    data::DataRequest req(aRequest, std::move(aCondition));
    std::vector<crow::json::wvalue> temp;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.complexSelect(req);
        for (size_t i = 0; i < req.size(); ++i)
        {
            temp.emplace_back(get::GetRouter::basicRouter(
                req.getTableName(i), req.getTableColumns(i), connection));
        }
    }

    for (size_t i = req.size() - 1; i >= 1; --i)
    {
        const auto& curName    = req.getNickname(i);
        const auto& oldName    = req.getTableName(i);
        auto parent     = req.getPreviousNum(i);
        const auto& targetName = req.getTableName(parent);

        for (size_t j = 0; j < temp[parent][targetName].size(); ++j)
        {
            temp[parent][targetName][j][curName] =
                std::move(temp[i][oldName][j]);
        }
    }

    result = std::move(temp[0]);

    return result;
}