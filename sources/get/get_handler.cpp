#include "get_handler.hpp"

#include <ranges>

#include "get_router.hpp"

crow::json::wvalue
get::GetHandler::singlGet(const std::string& aRequest,
                          const std::string& aCondition) noexcept
{
    crow::json::wvalue result;

    auto temp = mainGet(aRequest, aCondition);
    auto keys = temp.keys();
    if (keys.size() > 0 && temp[keys[0]].size() > 0)
    {
        result[keys[0]] = std::move(temp[keys[0]][0]);
    }

    return result;
}

crow::json::wvalue
get::GetHandler::multiplelGet(const std::string& aRequest,
                              const std::string& aCondition) noexcept
{
    crow::json::wvalue result = {401};

    auto temp = mainGet(aRequest, aCondition);
    auto keys = temp.keys();
    if (keys.size() > 0)
    {
        result[keys[0] + "s"] = std::move(temp[keys[0]]);
    }

    return result;
}

crow::json::wvalue
get::GetHandler::mainGet(const std::string& aRequest,
                         const std::string& aCondition) noexcept
{
    crow::json::wvalue result;

    data::DataRequest req(aRequest, aCondition);

    for (auto& i : req)
    {
        std::vector<crow::json::wvalue> temp;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            connection.val.handSelect(i);
            for (auto& j : i)
            {
                temp.emplace_back(get::GetRouter::basicRouter(
                    j.trueName, j.rowNumbers, connection));
            }
            connection.val.handClose();
        }

        for (size_t j = temp.size() - 1; j >= 1; --j)
        {
            auto& curName1   = i[j].jsonName;
            auto& curName2   = i[j].trueName;
            auto& targetNum  = i[j].parentNum;
            auto& targetName = i[targetNum].trueName;

            for (size_t k = 0; k < temp[targetNum][targetName].size(); ++k)
            {
                temp[targetNum][targetName][k][curName1] =
                    std::move(temp[j][curName2][k]);
            }
        }

        result = std::move(temp[0]);
    }

    return result;
}