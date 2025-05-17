#include "database_connection.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <vector>

#include "domain/log.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

#include "sql_wrapper.hpp"

//--------------------------------------------------------------------------------

std::unordered_map<data::ConnectionType, data::DBSettings>
data::DatabaseConnection::generateConnectionTypeSettings() noexcept
{
    std::unordered_map<ConnectionType, data::DBSettings> result;

    auto words = file::File::getWords("config", "database.pass");
    for (auto& i : words)
    {
        result[data::ConnectionType(std::stoi(i[0]))] =
            data::DBSettings{i[1], i[2], i[3], i[4]};
    }

    return result;
}

data::DBSettings
data::DatabaseConnection::getConnectionTypeSettings(
    const ConnectionType& aType) noexcept
{
    static std::unordered_map<ConnectionType, data::DBSettings> result =
        generateConnectionTypeSettings();
    return result[aType];
}

//--------------------------------------------------------------------------------

data::DatabaseConnection::DatabaseConnection(const DBSettings& aDBS) noexcept
    : mDBSettings(aDBS), mDatabase(aDBS)
{
    LOG_INFO("Creating_database_quare");
}

data::DatabaseConnection::DatabaseConnection(
    const ConnectionType& aType) noexcept
    : mDBSettings(getConnectionTypeSettings(aType)),
      mDatabase(getConnectionTypeSettings(aType))
{
    LOG_INFO("Creating_database_quare");
}

//--------------------------------------------------------------------------------

void
data::DatabaseConnection::complexSelect(const char* aRequest) noexcept
{
    mColumnNumber = 0;
    mDatabase.directSelect(aRequest);
}

int
data::DatabaseConnection::drop(const char* aTableName,
                               const char* aCondition) noexcept
{
    int res = -1;
    if (!aCondition.empty())
    {
        auto name = getTableName(aTableName);
        mDatabase.drop(name, aCondition);
        res = 1;
    }
    return res;
}

int
data::DatabaseConnection::dropByID(const char* aTableName,
                                   const std::vector<int>& aIDs) noexcept
{
    int res = -1;
    if (aIDs.size())
    {
        auto name = getTableName(aTableName);
        for (auto i : aIDs)
        {
            mDatabase.drop(name, "id=" + data::wrap(i));
        }
        res = 1;
    }
    return res;
}

//--------------------------------------------------------------------------------

void
data::DatabaseConnection::createTable(
    const char* aTableName,
    const std::vector<ColumnSetting>& aColums) noexcept
{
    mDatabase.createTable(getTableName(aTableName), aColums, mDBSettings.user);
}

void
data::DatabaseConnection::createEnvironment(
    const ConnectionType& aType) noexcept
{
    mDatabase.createEnvironment(getConnectionTypeSettings(aType));
}

void
data::DatabaseConnection::dropDatabase(const ConnectionType& aType) noexcept
{
    mDatabase.deleteDatabase(getConnectionTypeSettings(aType).name);
}

//--------------------------------------------------------------------------------

bool
data::DatabaseConnection::securityCheck(const char* aStr) noexcept
{
    bool result = true;

    int minusCnt = 0;
    for (auto c : aStr)
    {
        switch (c)
        {
            case '-':
                minusCnt++;
                break;
            case ';':
            case '\\':
            case '/':
            case '\'':
            case '\"':
                result = false;
            default:
                minusCnt = 0;
                break;
        }

        if (minusCnt > 1) result = false;
    }

    return result;
}

//--------------------------------------------------------------------------------

str::String
data::DatabaseConnection::getCell(const char* aTableName,
                                  const char* aColumnName,
                                  const char* aCondition) noexcept
{
    return mDatabase.getCell(getTableName(aTableName), aColumnName, aCondition);
}

//--------------------------------------------------------------------------------

str::String
data::DatabaseConnection::getTableName(const char* aTableName) const noexcept
{
    return mDBSettings.shame + "." + aTableName;
}
