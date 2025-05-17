#include "postgresql.hpp"

#include <codecvt>
#include <locale>

#include "text_data/cyrillic.hpp"

#include "pqxx/nontransaction"

#include "sql_wrapper.hpp"

#ifdef BILL_WINDOWS
#    define LOG_POSTGRES_QUERIES 1
#else
#    define LOG_POSTGRES_QUERIES 1
#endif

//--------------------------------------------------------------------------------

data::ColumnSetting::ColumnSetting(std::string aName,
                                   std::string aType,
                                   std::string aInfo) noexcept
    : name(aName), type(aType), info(aInfo)
{
}

data::Postgresql::Postgresql(const DBSettings& aDBS)
{
    LOG_INFO("Creating_postgresql_database_connection");
    try
    {
        // clang-format off
        mConnection = std::make_unique<pqxx::connection>(
            "dbname = "s     +   aDBS.name       + " "s +
            "user = "s       +   aDBS.user           + " "s +
            "password = "s   +   aDBS.password   + " "s +  
            "hostaddr = 127.0.0.1 port = 5432"s
        );
        // clang-format on
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Postgresql::Postgresql() ", e.what());
        // exit(0);
    }

    LOG_INFO("Opening_postgresql_database");
    if (mConnection->is_open())
    {
        LOG_INFO("Opened_database_successfully");
    }
    else
    {
        LOG_INFO("Can't_open_database");
        // exit(0);
    }
}

//--------------------------------------------------------------------------------

void
data::Postgresql::select(const std::string& aTableName,
                         const std::string& aColum,
                         const std::string& aCondition) noexcept
{
    std::string statement = "SELECT "s + (aColum == ""s ? "*"s : aColum) +
                            " FROM "s + aTableName +
                            (aCondition == ""s ? ""s : " WHERE "s) + aCondition;

    prepare(statement);
}

void
data::Postgresql::directSelect(const std::string& aRequest) noexcept
{
    prepare(aRequest);
}

std::string
data::Postgresql::getCell(const std::string& aTableName,
                          const std::string& aColumnName,
                          const std::string& aCondition) noexcept
{
    std::string statement = "SELECT "s + aColumnName + " FROM "s + aTableName +
                            " WHERE "s + aCondition;

    prepare(statement);
    step();
    std::string result = getRaw(0);
    // std::string result = getColumnAsStringUnsafe(0);
    closeStatment();
    return result;
}

void
data::Postgresql::closeStatment() noexcept
{
    if (mStatement != nullptr)
    {
        mStatement->commit();
        mStatement = nullptr;
    }
}

//--------------------------------------------------------------------------------

std::vector<int>
data::Postgresql::insert(const std::string& aTableName,
                         const std::string& aData) noexcept
{
    std::string statement =
        "INSERT INTO " + aTableName + " VALUES " + aData + " RETURNING id;";

    prepare(statement);

    std::vector<int> res;
    step();
    while (hasData(0))
    {
        res.emplace_back(getColumnIntUnsafe(0));
        step();
    }
    closeStatment();

    return res;
}

void
data::Postgresql::update(const std::string& aTableName,
                         const std::string& aData,
                         const std::string& aCondition) noexcept
{
    std::string statement =
        "UPDATE " + aTableName + " SET " + aData + " WHERE " + aCondition;
    exec(statement);
}

void
data::Postgresql::drop(const std::string& aTableName,
                       const std::string& aCondition) noexcept
{
    std::string statement =
        "DELETE FROM " + aTableName + " WHERE " + aCondition;
    exec(statement);
}

//--------------------------------------------------------------------------------

void
data::Postgresql::createEnvironment(const data::DBSettings& aDBS) noexcept
{
    auto& aDBName    = aDBS.name;
    auto& aUserName  = aDBS.user;
    auto& aPassword  = aDBS.password;
    auto& aShameName = aDBS.shame;

    std::string statement = "CREATE DATABASE " + aDBS.name + " ";
    statement += " WITH ENCODING \'ISO_8859_5\' ";
    statement += "LC_COLLATE=\'C\' LC_CTYPE=\'C\' ";
    statement += "TEMPLATE=template0";
    statement += ";";
    nontransaction(statement);

    exec("CREATE USER " + aDBS.user + " WITH PASSWORD \'" + aPassword + "\'");
    exec("ALTER ROLE " + aDBS.user + " SET client_encoding TO \'ISO_8859_5\'");
    exec("ALTER ROLE " + aUserName + " SET timezone TO 'UTC+3'");
    exec("GRANT ALL PRIVILEGES ON DATABASE " + aDBName + " TO " + aUserName);

    std::unique_ptr<pqxx::connection> temp = std::move(mConnection);
    // clang-format off
    mConnection = std::make_unique<pqxx::connection>(
        "dbname     = " +   aDBName         + " " +
        "user       = " +   aUserName       + " " +
        "password   = " +   aPassword       + " " +  
        "hostaddr   =       127.0.0.1       \
        port        =       5432"
    );
    // clang-format on

    exec("CREATE SCHEMA " + aShameName);
    exec("GRANT USAGE ON SCHEMA " + aShameName + " TO " + aUserName);
    exec("GRANT CREATE ON SCHEMA " + aShameName + " TO " + aUserName);
    exec("GRANT CONNECT ON DATABASE " + aDBName + " TO " + aUserName);

    mConnection = std::move(temp);
}

void
data::Postgresql::createTable(const std::string& aTableName,
                              const std::vector<ColumnSetting>& aColumns,
                              const std::string& aUserName) noexcept
{
    std::string statement = "CREATE TABLE " + aTableName + " ( ";

    statement += "id integer PRIMARY KEY,";
    for (auto& i : aColumns)
    {
        statement += i.name + " ";
        statement += i.type + " ";
        statement += i.info + " ";
        statement += ",";
    }
    statement.back() = ')';

    exec(statement);
    exec("ALTER TABLE " + aTableName + " OWNER TO " + aUserName);

    createSequence(aTableName, aUserName);
}

void
data::Postgresql::deleteDatabase(const std::string& aDBName) noexcept
{
    std::string statement = "DROP DATABASE " + aDBName;
    statement += ";";
    nontransaction(statement);
}

//--------------------------------------------------------------------------------

std::optional<int>
data::Postgresql::getColumnInt(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<std::optional<int>>();
}

std::optional<bool>
data::Postgresql::getColumnBool(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<std::optional<bool>>();
}

std::optional<const char*>
data::Postgresql::getColumnAsChars(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<std::optional<const char*>>();
}

std::optional<std::string>
data::Postgresql::getColumnAsString(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<std::optional<std::string>>();
}

//--------------------------------------------------------------------------------

int
data::Postgresql::getColumnIntUnsafe(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<int>();
}

float
data::Postgresql::getColumnFloatUnsafe(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<float>();
}

bool
data::Postgresql::getColumnBoolUnsafe(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<bool>();
}

const char*
data::Postgresql::getColumnAsCharsUnsafe(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<const char*>();
}

std::string
data::Postgresql::getColumnAsStringUnsafe(int aColumNumber) noexcept
{
    return mResultIterator[aColumNumber].as<std::string>();
}

std::string
data::Postgresql::getRaw(int aColumNumber) noexcept
{
    return std::string(mResultIterator[aColumNumber].c_str());
}

//--------------------------------------------------------------------------------

void
data::Postgresql::step() noexcept
{
    mResultIterator++;
}

bool
data::Postgresql::hasData(int num) const noexcept
{
    return !mResultIterator[num].is_null();
}

void
data::Postgresql::prepare(const std::string& aStatment) noexcept
{
#if LOG_POSTGRES_QUERIES
    LOG_INFO(aStatment);
#endif

    closeStatment();
    try
    {
        mStatement      = std::make_unique<pqxx::work>(*mConnection);
        mResult         = pqxx::result(mStatement->exec(aStatment.c_str()));
        mResultIterator = --mResult.begin();
    }
    catch (const pqxx::sql_error& e)
    {
        std::string s(e.what());
        // auto str = dom::Cyrilic::global.translit(s);
        LOG_ERROR(s, "req:", aStatment);
    }
}

void
data::Postgresql::exec(const std::string& aStatements) noexcept
{
    prepare(aStatements);
    // step();
    closeStatment();
}

void
data::Postgresql::nontransaction(const std::string& aStatment) noexcept
{
#if LOG_POSTGRES_QUERIES
    LOG_INFO(aStatment);
#endif

    try
    {
        pqxx::nontransaction w(*mConnection);
        w.exec(aStatment);
        w.commit();
    }
    catch (const pqxx::sql_error& e)
    {
        std::string s(e.what());
        // auto str = dom::Cyrilic::global.translit(s);
        LOG_ERROR(s, "req:", aStatment);
    }
}

//--------------------------------------------------------------------------------

void
data::Postgresql::createSequence(const std::string& aTableName,
                                 const std::string& aUserName) noexcept
{
    std::string sequenceName = aTableName + "_id_seq";

    exec("CREATE SEQUENCE " + sequenceName +
         " AS integer "
         " START WITH 1 "
         " INCREMENT BY 1 "
         " NO MINVALUE "
         " NO MAXVALUE "
         " CACHE 1 ");
    exec("ALTER TABLE " + sequenceName + " OWNER TO " + aUserName);
    exec("ALTER SEQUENCE " + sequenceName + " OWNED BY " + aTableName + ".id");
    exec("ALTER TABLE ONLY " + aTableName +
         " ALTER COLUMN id SET DEFAULT nextval(\' " + sequenceName +
         "\'::regclass)");
}

//--------------------------------------------------------------------------------
