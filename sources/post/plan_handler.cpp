#include "plan_handler.hpp"

#include <fstream>
#include <string>

crow::json::wvalue
post::PlanHandler::uploadFromFile(const crow::request& aReq)
{
    crow::json::wvalue res;
    crow::multipart::message msg(aReq);

    std::string type = msg.get_part_by_name("index").body;

    PlanData data;
    data.url = uploadFile(msg);

    if (type == "csv")
    {
        data.name      = msg.get_part_by_name("name").body;
        data.subjectID = std::stoi(msg.get_part_by_name("subject_id").body);
        res            = csvFileUpload(data);
    }

    return res;
}

crow::json::wvalue
post::PlanHandler::csvFileUpload(const PlanData& aPlanData)
{
    data::Table<data::Plan> plan(1);
    plan.back().name       = aPlanData.name;
    plan.back().subject_id = aPlanData.subjectID;
    plan.back().url        = aPlanData.url;

    {
        auto connection = data::ConnectionManager::getUserConnection();
        plan.back().id  = connection.val.update<data::Plan>(plan);
    }

    std::ifstream file(plan[0].url);
    std::string name;
    int count;
    data::Table<data::Theme> themes;
    while (std::getline(file, name, ';') && file >> count)
    {
        themes.emplace_back();
        themes.back().name       = name;
        themes.back().hour_count = count;
        themes.back().plan_id    = plan[0].id;
        std::getline(file, name, '\n');
    }

    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.update<data::Theme>(themes);
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
