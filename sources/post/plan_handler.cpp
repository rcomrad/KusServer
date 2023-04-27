#include "plan_handler.hpp"

#include <fstream>
#include <string>

crow::json::wvalue
post::PlanHandler::rawDataHandler(
    std::vector<std::vector<std::string>>& aData,
    const std::vector<std::vector<std::string>>& aAdditionalInfo) noexcept
{

    for (size_t i = 0; i < aData.size(); ++i)
    {
        data::Plan plan;
        plan.name       = aData[i][0];
        plan.subject_id = std::stoi(aData[i][1]);
        plan.url        = aData[i][2];

        {
            auto connection = data::ConnectionManager::getUserConnection();
            connection.val.insert<data::Plan>(plan);
        }

        data::DataArray<data::Theme> themes;
        if (aAdditionalInfo[i].size())
        {
            themes.emplace_back();
            themes.back().name       = aAdditionalInfo[i][0];
            themes.back().hour_count = std::stoi(aAdditionalInfo[i][1]);
            themes.back().plan_id    = plan.id;
        }
        {
            auto connection = data::ConnectionManager::getUserConnection();
            connection.val.update(themes);
        }
    }

    return {200};
}

// void
// post::PlanHandler::parseDataFile(std::string_view aFileName,
//                                  data::DatabaseQuery& aDBQ)
// {
//     std::ifstream inp(aFileName.data());

//     std::string s;
//     std::getline(inp, s);

//     int subjectID;
//     data::Table<data::Plan> plan;
//     while (inp >> subjectID)
//     {
//         plan.clear();
//         plan.emplace_back();

//         plan.back().subject_id = subjectID;
//         inp >> plan.back().name;
//         inp >> plan.back().url;
//         make(plan, aDBQ);
//     }
// }

/*
subjectID 		name 			url
    1			Тест	assets/upload/1a.csv
    1			C++		assets/upload/1.csv
*/
