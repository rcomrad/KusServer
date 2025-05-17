#include "get_handler.hpp"

#include <ranges>

#include "get_router.hpp"
#include "request_storage.hpp"

crow::json::wvalue
get::GetHandler::singlGet(const char* aRequest, const char* aCondition) noexcept
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
get::GetHandler::multiplelGet(const char* aRequest,
                              const char* aCondition) noexcept
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
get::GetHandler::mainGet(const char* aRequest, const char* aCondition) noexcept
{
    crow::json::wvalue result;

    auto req = RequestStorage::getRequest(aRequest);
    std::vector<crow::json::wvalue> temp;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.complexSelect(req.getFullStatement(aCondition));
        for (size_t i = 0; i < req.size; ++i)
        {
            temp.emplace_back(get::GetRouter::basicRouter(
                req[i].name, req[i].columnNums, connection));
        }
    }

    for (int i = req.size - 1; i >= 0; --i)
    {
        if (!req[i].additionalTable.empty())
        {
            auto& curBlock = temp[i][req[i].name];
            str::String name;
            for (int j = 0; j < curBlock.size(); ++j)
            {
                auto additionalTable = multiplelGet(
                    req[i].additionalTable,
                    req[i].name + "_id=" + curBlock[j]["id"].dump());
                if (name.empty()) name = additionalTable.keys()[0];
                curBlock[j][name] = std::move(additionalTable[name]);
            }
        }

        if (i)
        {
            const auto& curName    = req[i].nickname;
            const auto& oldName    = req[i].name;
            auto parent            = req[i].prev;
            const auto& targetName = req[parent].name;

            for (size_t j = 0; j < temp[parent][targetName].size(); ++j)
            {
                temp[parent][targetName][j][curName] =
                    std::move(temp[i][oldName][j]);
            }
        }
    }

    result = std::move(temp[0]);

    return result;
}
