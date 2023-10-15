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
