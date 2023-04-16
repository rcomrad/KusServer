#include "postgresql.hpp"

#include <codecvt>
#include <locale>

#include "domain/cyrillic.hpp"

#include "pqxx/nontransaction"

#include "sql_wrapper.hpp"

#ifdef BILL_WINDOWS
#    define LOG_POSTGRES_QUERIES 1
#else
#    define LOG_POSTGRES_QUERIES 1
#endif

//--------------------------------------------------------------------------------

data::Postgresql::Postgresql(const DBSettings& aDBS)
{
    WRITE_LOG("Creating_postgresql_database_connection");
    try
    {
        // clang-format off
        mConnection = std::make_unique<pqxx::connection>(
            "dbname = "     +   aDBS.name       + " " +
            "user = "       +   aDBS.user           + " " +
            "password = "   +   aDBS.password   + " " +  
            "hostaddr = 127.0.0.1 port = 5432"
        );
        // clang-format on
    }
    catch (const std::exception& e)
    {
        WRITE_ERROR("Postgresql::Postgresql() ", e.what());
        // exit(0);
    }

    WRITE_LOG("Opening_postgresql_database");
    if (mConnection->is_open())
    {
        WRITE_LOG("Opened_database_successfully");
    }
    else
    {
        WRITE_LOG("Can't_open_database");
        // exit(0);
    }
}

//--------------------------------------------------------------------------------

// std::vector<data::Type>
// data::Postgresql::getColumnTypes(const std::string& aTableName) noexcept
// {
//     std::vector<data::Type> result;

//     select(aTableName);
//     step();

//     for (const auto& i : mResultIterator)
//     {
//         auto type = i.type();
//         switch (type)
//         {
//             case 23: // int
//                 result.emplace_back(data::Type::INT);
//                 break;
//             case 16: // bool
//                 result.emplace_back(data::Type::BOOL);
//                 break;
//             case 1082: // data
//                 result.emplace_back(data::Type::STRING);
//                 break;
//             case 1043: // text
//                 result.emplace_back(data::Type::STRING);
//                 break;
//         }
//     }

//     closeStatment();
//     return result;
// }

// std::unordered_map<std::string, uint8_t>
// data::Postgresql::getColumnNames(const std::string& aTableName) noexcept
// {
//     std::unordered_map<std::string, uint8_t> result;

//     select(aTableName);
//     step();

//     int cnt = 0;
//     for (const auto& i : mResultIterator)
//     {
//         result[std::string(i.name())] = cnt++;
//     }

//     closeStatment();
//     return result;
// }

//--------------------------------------------------------------------------------

void
data::Postgresql::select(const std::string& aTableName,
                         const std::vector<std::string>& aColum,
                         const std::string& aConditon) noexcept
{
    std::string tableName = mShame + "."s + aTableName;
    auto colum            = merge(aColum);
    std::string statement = "SELECT "s + (colum == "" ? "*" : colum) +
                            " FROM " + tableName +
                            (aConditon == "" ? "" : " WHERE ") + aConditon;

    prepare({std::move(statement)});
}

//--------------------------------------------------------------------------------

int
data::Postgresql::insert(const std::string& aTableName,
                         const std::string& aData) noexcept
{
    std::string statement =
        "INSERT INTO " + aTableName + " VALUES " + aData + " RETURNING id;";

    prepare(statement);
    step();
    int res = 0;
    if (hasData(0)) res = getColumnIntUnsafe(0);
    closeStatment();

    return res;
}

void
data::Postgresql::update(const std::string& aTableName,
                         const std::string& aData,
                         const std::string& aConditon) noexcept
{
    std::string statement =
        "UPDATE " + aTableName + " SET " + aData + " WHERE " + aConditon;
    exec(statement);
}

void
data::Postgresql::drop(const std::string& aTableName,
                       const std::string& aConditon) noexcept
{
    std::string statement = "DELETE FROM " + aTableName + " WHERE " + aConditon;
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

    std::vector<std::string> statements;
    statements.reserve(4);

    statements.emplace_back("CREATE USER " + aDBS.user + " WITH PASSWORD \'" +
                            aPassword + "\'");
    statements.emplace_back("ALTER ROLE " + aDBS.user +
                            " SET client_encoding TO \'ISO_8859_5\'");
    statements.emplace_back("ALTER ROLE " + aUserName +
                            " SET timezone TO 'UTC+3'");
    statements.emplace_back("GRANT ALL PRIVILEGES ON DATABASE " + aDBName +
                            " TO " + aUserName);
    exec(statements);

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

    statements.clear();
    statements.reserve(4);

    statements.emplace_back("CREATE SCHEMA " + aShameName);
    statements.emplace_back("GRANT USAGE ON SCHEMA " + aShameName + " TO " +
                            aUserName);
    statements.emplace_back("GRANT CREATE ON SCHEMA " + aShameName + " TO " +
                            aUserName);
    statements.emplace_back("GRANT CONNECT ON DATABASE " + aDBName + " TO " +
                            aUserName);
    exec(statements);

    mConnection = std::move(temp);
}

void
data::Postgresql::createTable(
    const std::string& aTableName,
    const std::vector<ColumnSetting>& aColumns) noexcept
{
    std::string tableName = mShame + "." + aTableName;
    std::string statement = "CREATE TABLE " + tableName + " ( ";

    statement += "id integer PRIMARY KEY,";
    for (auto& i : aColumns)
    {
        statement += i.name + " ";
        statement += i.type + " ";
        statement += i.info + " ";
        statement += ", ";
    }
    statement[statement.size() - 2] = ')';

    std::vector<std::string> statements;
    statements.reserve(2);

    statements.emplace_back(std::move(statement));
    statements.emplace_back("ALTER TABLE " + tableName + " OWNER TO " + mUser);
    exec(statements);

    createSequence(aTableName);
}

void
data::Postgresql::deleteDatabase(const std::string& aDBName,
                                 const std::string& aUserName) noexcept
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
data::Postgresql::closeStatment() noexcept
{
    mStatement->commit();
    mStatement = nullptr;
}

void
data::Postgresql::prepare(const std::string& aStatment) noexcept
{
#if LOG_POSTGRES_QUERIES
    std::cout << aStatment << "\n";
#endif

    try
    {
        mStatement      = std::make_unique<pqxx::work>(*mConnection);
        mResult         = pqxx::result(mStatement->exec(aStatment.c_str()));
        mResultIterator = --mResult.begin();
    }
    catch (const pqxx::sql_error& e)
    {
        std::string s(e.what());
        auto str = dom::Cyrilic::global.translit(s);
        WRITE_ERROR("Postgresql::prepare() ", str);
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
    std::cout << aStatment << "\n";
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
        auto str = dom::Cyrilic::global.translit(s);
        WRITE_ERROR(str);
    }
}

//--------------------------------------------------------------------------------

void
data::Postgresql::createSequence(const std::string& aTableName) noexcept
{
    std::string tableName    = mShame + "." + aTableName;
    std::string sequenceName = mShame + "." + aTableName + "_id_seq";

    std::vector<std::string> statements;
    statements.reserve(4);
    statements.emplace_back("CREATE SEQUENCE " + sequenceName +
                            " AS integer "
                            " START WITH 1 "
                            " INCREMENT BY 1 "
                            " NO MINVALUE "
                            " NO MAXVALUE "
                            " CACHE 1 ");
    statements.emplace_back("ALTER TABLE " + sequenceName + " OWNER TO " +
                            mUser);
    statements.emplace_back("ALTER SEQUENCE " + sequenceName + " OWNED BY " +
                            tableName + ".id");
    statements.emplace_back("ALTER TABLE ONLY " + tableName +
                            " ALTER COLUMN id SET DEFAULT nextval(\' " +
                            sequenceName + "\'::regclass)");
    exec(statements);
}

//--------------------------------------------------------------------------------
