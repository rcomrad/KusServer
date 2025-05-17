#include "plan_handler.hpp"

#include <fstream>
#include <string>

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
    //         themes.back().plan_id    = plan.id;
    //     }
    //     {
    //         auto connection = data::ConnectionManager::getUserConnection();
    //         connection.val.insert(themes);
    //     }
    // }

    data::Plan plan;
    plan.name       = aData.header["name"];
    plan.subject_id = std::stoi(aData.header["subject_id"]);
    plan.url        = aData.header["url"];

    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.insert<data::Plan>(plan);
    }

    data::DataArray<data::Theme> themes;
    for (auto& i : aData.value)
    {
        themes.emplace_back();
        themes.back().name       = i[0];
        themes.back().hour_count = std::stoi(i[1]);
        themes.back().plan_id    = plan.id;
    }

    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.insert(themes);
    }

    return {200};
}
