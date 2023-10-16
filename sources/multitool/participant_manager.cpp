#include "participant_manager.hpp"

#include "domain/url_wrapper.hpp"

#include "database/connection_manager.hpp"

#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"

mult::PaticipantManager mult::PaticipantManager::mInstance;

mult::PaticipantManager::PaticipantManager() noexcept
    : ModuleBase("user=comp", file::Value::Type::String)
{
}

std::string
mult::PaticipantManager::doAction() noexcept
{
    static auto& command = core::VariableStorage::touchWord("user=comp");
    return userComp(command);
}

std::string
mult::PaticipantManager::userComp(const std::string aValue) noexcept
{
    auto data      = file::Parser::slice(aValue, "=");
    auto& userPref = data[0];
    int compId     = std::stoi(data[1]);

    auto connection = data::ConnectionManager::getUserConnection();
    auto users      = connection.val.getDataArray<data::User>();

    data::DataArray<data::CompetitionUser> arr;
    for (auto& u : users)
    {
        if (u.login.find(userPref) != std::string::npos)
        {
            data::CompetitionUser c;
            c.competitionID = compId;
            c.userID        = u.id;
            arr.emplace_back(std::move(c));
        }
    }
    connection.val.write(arr);

    return "sus";
}

mult::CompetitionManager mult::CompetitionManager::mInstance;

mult::CompetitionManager::CompetitionManager() noexcept
    : ModuleBase("comp=question", file::Value::Type::String)
{
}

std::string
mult::CompetitionManager::doAction() noexcept
{
    static auto& command = core::VariableStorage::touchWord("comp=question");
    return userComp(command);
}

std::string
mult::CompetitionManager::userComp(const std::string aValue) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    auto data          = file::Parser::slice(aValue, "=");
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

    return "sus";
}
