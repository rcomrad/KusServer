#include "competition_manager.hpp"

#include "database/connection_manager.hpp"

#include "domain/url_wrapper.hpp"
#include "domain/variable_storage.hpp"

#include "text_data/file.hpp"
#include "text_data/parser.hpp"
#include "text_data/path.hpp"

//--------------------------------------------------------------------------------

route::RouterNode mod::CompetitionManager::glRouter(
    "main", "comp", (void*)&mod::CompetitionManager::applyCommand);

//--------------------------------------------------------------------------------

std::string
mod::CompetitionManager::applyCommand(const route::Command& aCommand) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    if (aCommand.value == "comp=question")
    {
        return userComp(*aCommand.arguments.begin());
    }
    return "LOG_ERROR";
}

// data::Competition
// mod::CompetitionManager::userComp(const std::string aValue) noexcept
// {
//     data::Competition result;
//     bool needWritingToDB = false;

//     auto it = aVal
// }

std::string
mod::CompetitionManager::userComp(const std::string aValue) noexcept
{

    auto connection = data::ConnectionManager::getUserConnection();

    auto data          = text::Parser::slice(aValue, "=");
    auto& questionPref = data[1];

    data::Competition comp;
    comp.name      = data[0];
    comp.startTime = "2020-10-16 14:00:00";
    comp.endTime   = "2030-10-16 14:00:00";
    connection.val.write(comp);

    data::DataArray<data::CompetitionQuestion> arr;
    auto questions = connection.val.getDataArray<data::Question>();
    for (auto& q : questions)
    {
        if (q.nickname.find(questionPref) != std::string::npos)
        {
            data::CompetitionQuestion c;
            c.competitionID = comp.id;
            c.questionID    = q.id;
            c.name          = q.name;
            arr.emplace_back(std::move(c));
        }
    }
    connection.val.write(arr);

    return "TODO: result";
}
