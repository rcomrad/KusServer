#include "database_connection.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <vector>

#include "domain/error_message.hpp"

#include "sql_wrapper.hpp"

//--------------------------------------------------------------------------------

std::unordered_map<data::ConnectionType, data::DBSettings>
    data::DatabaseConnection::mConnectionTypeSettings =
        getConnectionTypeSettings();

std::unordered_map<data::ConnectionType, data::DBSettings>
data::DatabaseConnection::getConnectionTypeSettings() noexcept
{
    std::unordered_map<ConnectionType, data::DBSettings> result;

    std::ifstream inp("database.pass");
    data::DBSettings DBS;
    int num;
    while (inp >> num)
    {
        inp >> DBS.name;
        inp >> DBS.user;
        inp >> DBS.password;
        inp >> DBS.shame;

        result[data::ConnectionType(num)] = DBS;
    }

    return result;
}

//--------------------------------------------------------------------------------

data::DatabaseConnection::DatabaseConnection(const DBSettings& aDBS) noexcept
    : mDBSettings(aDBS), mDatabase(aDBS)
{
    WRITE_LOG("Creating_database_quare");
}

data::DatabaseConnection::DatabaseConnection(
    const ConnectionType& aType) noexcept
    : mDatabase(mConnectionTypeSettings[aType])
{
    WRITE_LOG("Creating_database_quare");
}

//--------------------------------------------------------------------------------

void
data::DatabaseConnection::complexSelect(
    const data::DataRequest& request) noexcept
{
    mColumnNumber = 0;
    auto tabl     = request.getTables();
    auto col      = request.getColumns();
    auto con      = request.getCondition();
    mDatabase.select(tabl, col, con);
}

//--------------------------------------------------------------------------------

void
data::DatabaseConnection::createTable(
    const std::string& aTableName,
    const std::vector<ColumnSetting>& aColums) noexcept
{
    mDatabase.createTable(aTableName, aColums, mDBSettings.user);
}

void
data::DatabaseConnection::createEnvironment(
    const ConnectionType& aType) noexcept
{
    mDatabase.createEnvironment(mConnectionTypeSettings[aType]);
}

void
data::DatabaseConnection::dropDatabase(const ConnectionType& aType) noexcept
{
    mDatabase.deleteDatabase(mConnectionTypeSettings[aType].name);
}

//--------------------------------------------------------------------------------
