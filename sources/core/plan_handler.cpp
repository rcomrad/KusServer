#include "plan_handler.hpp"

#include <fstream>
#include <string>

void
core::PlanHandler::loadFromFile(std::string_view aFileName,
                                data::DatabaseQuery& aDBQ)
{
    std::ifstream inp(aFileName.data());

    std::string s;
    std::getline(inp, s);

    int subjectID;
    data::Table<data::Plan> plan;
    while (inp >> subjectID)
    {
        plan.clear();
        plan.emplace_back();

        plan.back().subject_id = subjectID;
        inp >> plan.back().name;
        inp >> plan.back().url;
        make(plan, aDBQ);
    }
}

void
core::PlanHandler::loadFromRequest(const crow::request& aReq,
                                   data::DatabaseQuery& aDBQ)
{
    crow::multipart::message msg(aReq);
    for (auto& i : msg.parts)
    {
        std::cout << i.body << "\n";
    }

    data::Table<data::Plan> plan(1);
    plan.back().name       = msg.get_part_by_name("name").body;
    plan.back().subject_id = std::stoi(msg.get_part_by_name("subject_id").body);
    plan.back().url        = uploadFile(msg, aDBQ);

    make(plan, aDBQ);
}

void
core::PlanHandler::make(data::Table<data::Plan>& aPlan,
                        data::DatabaseQuery& aDBQ)
{
    aDBQ.insert<data::Plan>(aPlan);
    aPlan = aDBQ.getData<data::Plan>("url = " + data::wrap(aPlan[0].url));
    std::ifstream file(aPlan[0].url);

    std::string name;
    int count;
    data::Table<data::Theme> themes;
    while (std::getline(file, name, ';') && file >> count)
    {
        themes.emplace_back();
        themes.back().name       = name;
        themes.back().hour_count = count;
        themes.back().plan_id    = aPlan[0].id;
        std::getline(file, name, '\n');
    }
    aDBQ.insert<data::Theme>(themes);
}
