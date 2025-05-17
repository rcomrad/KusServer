#include "plan_handler.hpp"

#include <fstream>
#include <string>

#include "database/safe_sql_wrapper.hpp"

crow::json::wvalue
post::PlanHandler::rawDataHandler(data::RawData& aData) noexcept
{

    // for (size_t i = 0; i < aData.value.size(); ++i)
    // {
    //     data::Plan plan;
    //     plan.name       = aData.header["name"];
    //     plan.subject_id = std::stoi(aData.header["subject_id"]);
    //     plan.url        = aData.header["url"];

    //     {
    //         auto connection = data::ConnectionManager::getUserConnection();
    //         connection.val.insert<data::Plan>(plan);
    //     }

    //     data::DataArray<data::Theme> themes;
    //     if (aData.additionalInfo[i].size())
    //     {
    //         themes.emplace_back();
    //         themes.back().name       = aData.additionalInfo[i][0];
    //         themes.back().hour_count = std::stoi(aData.additionalInfo[i][1]);
    //         themes.back().planID    = plan.id;
    //     }
    //     {
    //         auto connection = data::ConnectionManager::getUserConnection();
    //         connection.val.insert(themes);
    //     }
    // }

    auto nameIt      = aData.header.find("name");
    auto subjectIDIt = aData.header.find("subject_id");
    auto urlIt       = aData.header.find("url");

    if (nameIt != aData.header.end() && subjectIDIt != aData.header.end() &&
        urlIt != aData.header.end())
    {
        data::Plan plan;

        plan.name      = nameIt->second;
        plan.subjectID = std::stoi(subjectIDIt->second);
        plan.url       = urlIt->second;

        {
            auto connection = data::ConnectionManager::getUserConnection();
            connection.val.insert<data::Plan>(plan);
        }

        data::DataArray<data::Theme> themes;
        for (auto& i : aData.value)
        {
            themes.emplace_back();
            themes.back().name      = i[0];
            themes.back().hourCount = std::stoi(i[1]);
            themes.back().planID    = plan.id;
        }

        {
            auto connection = data::ConnectionManager::getUserConnection();
            connection.val.insert(themes);
        }
    }

    return {200};
}
