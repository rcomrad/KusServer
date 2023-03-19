#include "get_handler.hpp"

#include <ranges>

#include "get_router.hpp"

crow::json::wvalue
get::GetHandler::mainGet(const std::string& aRequest,
                         const std::string& aCondition,
                         data::DBSettings& aDBS) noexcept
{
    crow::json::wvalue result;

    data::DataRequest req(aRequest, aCondition);
    data::DatabaseQuery dbq(aDBS);
    for (auto& i : req)
    {
        dbq.handSelect(i);

        // crow::json::wvalue::list temp;
        std::vector<crow::json::wvalue> temp;
        for (auto& j : i)
        {
            // result = get::GetRouter::basicRouter(j.trueName, j.rowNumbers,
            // dbq);
            temp.emplace_back(
                get::GetRouter::basicRouter(j.trueName, j.rowNumbers, dbq));
        }
        dbq.handClose();

        // for (auto& i : std::ranges::reverse_view(temp))
        for (size_t j = temp.size() - 1; j >= 1; --j)
        {
            auto& curName    = i[j].jsonName;
            auto num         = i[j].parentNum;
            auto& targetName = i[num].jsonName;

            for (size_t k = 0; k < temp[num][targetName].size(); ++k)
            {
                temp[num][targetName][k][curName] =
                    std::move(temp[j][curName][k]);
            }
        }

        result = std::move(temp[0]);
    }

    return result;
}