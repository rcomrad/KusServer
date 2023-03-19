#define DUMMY_NAME "r456rq452rrrr"s
#define DUMMY_NUM  int(2e9)

#include "database_query.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <set>
#include <vector>

#include "domain/error_message.hpp"

#include "sql_wrapper.hpp"

data::DatabaseQuery::DatabaseQuery(const DBSettings& aDBS) noexcept
    : mDatabase(aDBS)
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
data::DatabaseQuery::createEnvironment(const DBSettings& aDBS) noexcept
{
    mDatabase.createEnvironment(aDBS);
}

void
data::DatabaseQuery::dropDatabase(const DBSettings& aDBS) noexcept
{
    mDatabase.deleteDatabase(aDBS.name);
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
