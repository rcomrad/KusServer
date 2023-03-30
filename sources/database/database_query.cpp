#define DUMMY_NAME "r456rq452rrrr"s
#define DUMMY_NUM  int(2e9)

#include "database_query.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <set>
#include <vector>

#include "domain/error_message.hpp"

#include "sql_wrapper.hpp"

//--------------------------------------------------------------------------------

std::unordered_map<data::DatabaseQuery::UserType, data::DBSettings>
    data::DatabaseQuery::mUserTypeSettings = getUserTypeSettings();

std::unordered_map<data::DatabaseQuery::UserType, data::DBSettings>
data::DatabaseQuery::getUserTypeSettings() noexcept
{
    std::unordered_map<UserType, data::DBSettings> result;

    std::ifstream inp("database.pass");
    data::DBSettings DBS;
    int num;
    while (inp >> num)
    {
        inp >> DBS.name;
        inp >> DBS.user;
        inp >> DBS.password;
        inp >> DBS.shame;

        result[data::DatabaseQuery::UserType(num)] = DBS;
    }

    return result;
}

//--------------------------------------------------------------------------------

data::DatabaseQuery::DatabaseQuery(const DBSettings& aDBS) noexcept
    : mDatabase(aDBS)
{
    WRITE_LOG("Creating_database_quare");
}

data::DatabaseQuery::DatabaseQuery(const UserType& aType) noexcept
    : mDatabase(mUserTypeSettings[aType])
{
    WRITE_LOG("Creating_database_quare");
}

//--------------------------------------------------------------------------------

void
data::DatabaseQuery::createTable(
    const std::string& aTableName,
    const std::vector<ColumnSetting>& aColums) noexcept
{
    mDatabase.createTable(aTableName, aColums);
}

void
data::DatabaseQuery::createEnvironment(const UserType& aType) noexcept
{
    mDatabase.createEnvironment(mUserTypeSettings[aType]);
}

void
data::DatabaseQuery::dropDatabase(const UserType& aType) noexcept
{
    mDatabase.deleteDatabase(mUserTypeSettings[aType].name,
                             mUserTypeSettings[aType].user);
}

//--------------------------------------------------------------------------------

std::vector<data::Type>
data::DatabaseQuery::getColumnTypes(const std::string& aTableName) noexcept
{
    return mDatabase.getColumnTypes(aTableName);
}

std::unordered_map<std::string, uint8_t>
data::DatabaseQuery::getColumnNames(const std::string& aTableName) noexcept
{
    return mDatabase.getColumnNames(aTableName);
}

//--------------------------------------------------------------------------------

int
data::DatabaseQuery::insert(const std::string& aTableName,
                            const std::vector<std::string>& aData) noexcept
{
    return mDatabase.insert(aTableName, aData);
}
