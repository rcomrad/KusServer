#include "participant_manager.hpp"

#include "domain/url_wrapper.hpp"

#include "database/connection_manager.hpp"

#include "domain/variable_storage.hpp"
#include "text_data/file.hpp"
#include "text_data/parser.hpp"
#include "text_data/path.hpp"

mod::PaticipantManager mod::PaticipantManager::mInstance;

mod::PaticipantManager::PaticipantManager() noexcept : ModuleBase({"user=comp"})
{
}

std::string
mod::PaticipantManager::doAction(const Command& aComman) noexcept
{
    return userComp(aComman.argument);
}

std::string
mod::PaticipantManager::userComp(const std::string aValue) noexcept
{
    auto data      = text::Parser::slice(aValue, "=");
    auto& userPref = data[0];
    // bool flagg     = data[1].back() == '-';
    // if (flagg) data[1].pop_back();
    int compId = std::stoi(data[1]);

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
