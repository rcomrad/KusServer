#include "database_connection.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <vector>

#include "domain/error_message.hpp"

#include "file/file.hpp"

#include "sql_wrapper.hpp"

//--------------------------------------------------------------------------------

std::unordered_map<data::ConnectionType, data::DBSettings>
data::DatabaseConnection::generateConnectionTypeSettings() noexcept
{
    std::unordered_map<ConnectionType, data::DBSettings> result;

    auto words = file::File::getWords("database.pass", true);
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
    WRITE_LOG("Creating_database_quare");
}

data::DatabaseConnection::DatabaseConnection(
    const ConnectionType& aType) noexcept
    : mDBSettings(getConnectionTypeSettings(aType)),
      mDatabase(getConnectionTypeSettings(aType))
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

int
data::DatabaseConnection::dropByID(const std::string& aTableName,
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
    const std::string& aTableName,
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
data::DatabaseConnection::securityCheck(const std::string& aStr) noexcept
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

std::string
data::DatabaseConnection::getCell(const std::string& aTableName,
                                  const std::string& aColumnName,
                                  const std::string& aCondition) noexcept
{
    return mDatabase.getCell(getTableName(aTableName), aColumnName, aCondition);
}

//--------------------------------------------------------------------------------

std::string
data::DatabaseConnection::getTableName(
    const std::string& aTableName) const noexcept
{
    return mDBSettings.shame + "." + aTableName;
}
