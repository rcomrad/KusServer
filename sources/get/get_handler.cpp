#include "get_handler.hpp"

#include <ranges>

#include "get_router.hpp"
#include "request_storage.hpp"

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

// crow::json::wvalue
// get::GetHandler::mainGet(const std::string& aRequest,
//                          const std::string& aCondition) noexcept
// {
//     crow::json::wvalue result;

//     auto req = RequestStorage::getRequest(aRequest);
//     std::vector<crow::json::wvalue> temp;
//     {
//         auto connection = data::ConnectionManager::getUserConnection();
//         connection.val.complexSelect(req.getFullStatement(aCondition));
//         for (size_t i = 0; i < req.size; ++i)
//         {
//             temp.emplace_back(get::GetRouter::basicRouter(
//                 req[i].name, req[i].columnNums, connection));
//         }
//     }

//     for (size_t i = req.size - 1; i >= 1; --i)
//     {
//         const auto& curName    = req[i].nickname;
//         const auto& oldName    = req[i].name;
//         auto parent            = req[i].prev;
//         const auto& targetName = req[parent].name;

//         for (size_t j = 0; j < temp[parent][targetName].size(); ++j)
//         {
//             temp[parent][targetName][j][curName] =
//                 std::move(temp[i][oldName][j]);
//         }
//     }

//     result = std::move(temp[0]);

//     return result;
// }

crow::json::wvalue
get::GetHandler::mainGet(const std::string& aRequest,
                         const std::string& aCondition) noexcept
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
            // auto d0 = temp[i].dump();
            // auto d1 = temp[i][req[i].name].dump();
            // auto d2 = temp[i][req[i].name][0].dump();
            // auto d3 = temp[i][req[i].name][0]["id"].dump();

            auto& curBlock = temp[i][req[i].name];
            std::string name;
            for (int j = 0; j < curBlock.size(); ++j)
            {
                auto additionalTable =
                    multiplelGet(req[i].additionalTable,
                            req[i].name + "_id=" + curBlock[j]["id"].dump());
                if (name.empty()) name = additionalTable.keys()[0];
                curBlock[j][name] = std::move(additionalTable[name]);

                // auto dd0 = additionalTable.dump();
                // auto dd1 = additionalTable[name].dump();
                // auto dd2 = temp[i][req[i].name].dump();
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

// crow::json::wvalue
// get::GetHandler::mainGet(const std::string& aRequest,
//                          const std::string& aCondition) noexcept
// {
//     crow::json::wvalue result;

//     auto req = RequestStorage::getRequest(aRequest);
//     std::vector<crow::json::wvalue> temp =
//         runRequest(req.getFullStatement(aCondition), req.size);

//     for (size_t i = req.size - 1; i >= 1; --i)
//     {
//         if (req[i].additionalTable)
//         {
//         }

//         const auto& curName    = req[i].nickname;
//         const auto& oldName    = req[i].name;
//         auto parent            = req[i].prev;
//         const auto& targetName = req[parent].name;

//         for (size_t j = 0; j < temp[parent][targetName].size(); ++j)
//         {
//             temp[parent][targetName][j][curName] =
//                 std::move(temp[i][oldName][j]);
//         }
//     }

//     for (size_t i = req.size - 1; i >= 1; --i)
//     {
//         const auto& curName    = req[i].nickname;
//         const auto& oldName    = req[i].name;
//         auto parent            = req[i].prev;
//         const auto& targetName = req[parent].name;

//         for (size_t j = 0; j < temp[parent][targetName].size(); ++j)
//         {
//             temp[parent][targetName][j][curName] =
//                 std::move(temp[i][oldName][j]);
//         }
//     }

//     result = std::move(temp[0]);

//     return result;
// }

// std::vector<crow::json::wvalue>
// get::GetHandler::runRequest(const std::string& aRequest, int aSize) noexcept
// {
//     std::vector<crow::json::wvalue> result;

//     {
//         auto connection = data::ConnectionManager::getUserConnection();
//         connection.val.complexSelect(aRequest);
//         for (size_t i = 0; i < aSize; ++i)
//         {
//             result.emplace_back(get::GetRouter::basicRouter(
//                 req[i].name, req[i].columnNums, connection));
//         }
//     }

//     return result;
// }
