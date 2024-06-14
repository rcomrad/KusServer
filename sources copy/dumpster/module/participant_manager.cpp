#include "participant_manager.hpp"

#include "domain/url_wrapper.hpp"

#include "core/variable_storage.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"

mod::PaticipantManager mod::PaticipantManager::mInstance;

mod::PaticipantManager::PaticipantManager() noexcept : ModuleBase({"user=comp"})
{
}

str::String
mod::PaticipantManager::doAction(const Command& aComman) noexcept
{
    return userComp(aComman.argument);
}

str::String
mod::PaticipantManager::userComp(const str::String aValue) noexcept
{
    auto data      = file::Parser::slice(aValue, "=");
    auto& userPref = data[0];
    // bool flagg     = data[1].back() == '-';
    // if (flagg) data[1].pop_back();
    int compId = std::stoi(data[1]);

    auto connection = data::ConnectionManager::getUserConnection();
    auto users      = connection.val.getDataArray<data::User>();

    data::DataArray<data::CompetitionUser> arr;
    for (auto& u : users)
    {
        if (u.login.find(userPref) != str::String::npos)
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
