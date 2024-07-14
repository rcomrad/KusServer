#include "sql_connection.hpp"

#include <cstring>

#include "string/string_malloc.hpp"

#include "struct_storage.hpp"

data::SQLConnection::SQLConnection(const Credentials& a_credentials) noexcept
    : m_db_conn(a_credentials)
{
}

word_t
data::SQLConnection::insert(void* a_result_ptr,
                            struct_id_t a_struct_id) noexcept
{
    auto struct_data = StructStorage::getStructData(a_struct_id);
    MALLOC_STR(statement, getInsertStatementSize(struct_data));
    auto cur_char_ptr = statement;

    //----------------------------------------------------------------------------

    SPRINTF(cur_char_ptr, "INSERT INTO %s VALUES (", struct_data.name);

    for (struct_id_t i = 0; i < struct_data.count; ++i)
    {
        switch (struct_data.vars[i].type)
        {
            case CPPTypeEnum::INT:
                SPRINTF(cur_char_ptr, "%d,", *(int*)a_result_ptr);
                break;
            case CPPTypeEnum::BOOL:
                SPRINTF(cur_char_ptr,
                        (*(bool*)a_result_ptr) ? "true" : "false");
                break;
            case CPPTypeEnum::FLOAT:
                SPRINTF(cur_char_ptr, "%f,", *(float*)a_result_ptr);
                break;
        }

        a_result_ptr = ((char*)a_result_ptr) + struct_data.vars[i].size;
    }

    SPRINTF(cur_char_ptr, ") RETURNING id;");

    //----------------------------------------------------------------------------

    m_db_conn.exec(statement);
    m_db_conn.step();
    word_t res = m_db_conn.getInt(0);
    m_db_conn.closeStatement();

    return res;
}

void
data::SQLConnection::select(void* a_result_ptr,
                            struct_id_t a_struct_id,
                            const char* a_condition) noexcept
{
    auto struct_data = StructStorage::getStructData(a_struct_id);
    MALLOC_STR(statement, getSelectStatementSize(struct_data, a_condition));
    auto cur_char_ptr = statement;

    SPRINTF(cur_char_ptr, "SELECT ");
    if (true)
    {
        SPRINTF(cur_char_ptr, " * ");
    }
    SPRINTF(cur_char_ptr, " FROM ");
    SPRINTF(cur_char_ptr, "%s", struct_data.name);
    if (a_condition != nullptr)
    {
        SPRINTF(cur_char_ptr, " WHERE ");
        SPRINTF(cur_char_ptr, "%s", a_condition);
    }
    SPRINTF(cur_char_ptr, ";");

    //----------------------------------------------------------------------------

    m_db_conn.exec(statement);
    m_db_conn.step();

    //----------------------------------------------------------------------------

    for (struct_id_t i = 0; i < struct_data.count; ++i)
    {
        // skipping unselected columns
        // if (!a_selected_colums[i] &&
        //     !a_selected_columns[DatabaseStructVarMaxCount])
        // {
        //     continue;
        // }

        switch (struct_data.vars[i].type)
        {
            case CPPTypeEnum::INT:
                *((int*)a_result_ptr) = m_db_conn.getInt(i);
                break;
            case CPPTypeEnum::BOOL:
                *((bool*)a_result_ptr) = m_db_conn.getBool(i);
                break;
            case CPPTypeEnum::FLOAT:
                *((float*)a_result_ptr) = m_db_conn.getFloat(i);
                break;
        }

        a_result_ptr = ((char*)a_result_ptr) + struct_data.vars[i].size;
    }

    //----------------------------------------------------------------------------

    m_db_conn.closeStatement();
}

void
data::SQLConnection::createEnvironment(
    const Credentials& a_credentials) noexcept
{
    MALLOC_STR(statement, 200);
    auto cur_char_ptr = statement;

    const auto& cred          = a_credentials.m_credentials.fields;
    const auto& database_name = cred.name;
    const auto& user_name     = cred.user;
    const auto& password      = cred.password;
    const auto& shame         = cred.shame;

    SPRINTF(cur_char_ptr,
            "CREATE DATABASE %s  WITH ENCODING 'ISO_8859_5' "
            "LC_COLLATE='C' LC_CTYPE='C' TEMPLATE=template0;",
            database_name);

    m_db_conn.nontransaction(statement);
    cur_char_ptr    = statement;
    cur_char_ptr[0] = 0;

    SPRINTF(cur_char_ptr, "CREATE USER %s WITH PASSWORD '%s';", user_name,
            password);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr, "ALTER ROLE %s SET client_encoding TO 'ISO_8859_5';",
            user_name);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr, "ALTER ROLE %s SET timezone TO 'UTC+3';", user_name);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr, "GRANT ALL PRIVILEGES ON DATABASE %s TO %s;",
            database_name, user_name);
    execAndReset(statement, cur_char_ptr);

    // std::unique_ptr<pqxx::connection> temp = std::move(mConnection);
    // // clang-format off
    // mConnection = std::make_unique<pqxx::connection>(
    //     "dbname     = " +   aDBName         + " " +
    //     "user       = " +   aUserName       + " " +
    //     "password   = " +   aPassword       + " " +
    //     "hostaddr   =       127.0.0.1       \
    //     port        =       5432"
    // );
    // // clang-format on

    // exec("CREATE SCHEMA " + aShameName);
    // exec("GRANT USAGE ON SCHEMA " + aShameName + " TO " + aUserName);
    // exec("GRANT CREATE ON SCHEMA " + aShameName + " TO " + aUserName);
    // exec("GRANT CONNECT ON DATABASE " + aDBName + " TO " + aUserName);

    // mConnection = std::move(temp);
}

// void
// mod::Populate::remakeDatabase() noexcept
// {
//     createEnvironment();
//     createDatabaseFromFile(
//         core::Path::getPathUnsafe("config", "database.psql_db"));
//     post::PostHandler::uploadFromFile(
//         {
//             {"type", "nun"}
//     },
//         core::Path::getPathUnsafe("config", "database.dmp"));
// }

void
data::SQLConnection::createTable(const char* a_owner_name,
                                 const char* a_table_name,
                                 const char* a_table_body) noexcept
{
    MALLOC_STR(statement, 200);
    auto cur_char_ptr = statement;

    SPRINTF(cur_char_ptr, "CREATE TABLE %s (id integer PRIMARY KEY,%s);",
            a_table_name, a_table_body);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr, "ALTER TABLE %s OWNER TO %s;", a_table_name,
            a_owner_name);
    execAndReset(statement, cur_char_ptr);

    //----------------------------------------------------------------------------

    SPRINTF(cur_char_ptr,
            "CREATE SEQUENCE %s_id_seq AS integer START WITH 1 "
            "INCREMENT BY 1 NO MINVALUE NO MAXVALUE CACHE 1;",
            a_table_name);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr, "ALTER TABLE %s_id_seq OWNER TO %s;", a_table_name,
            a_owner_name);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr, "ALTER SEQUENCE %s_id_seq OWNED BY %s.id;",
            a_table_name, a_table_name);
    execAndReset(statement, cur_char_ptr);

    SPRINTF(cur_char_ptr,
            "ALTER TABLE ONLY %s ALTER COLUMN id SET DEFAULT "
            "nextval('%s_id_seq'::regclass);",
            a_table_name, a_table_name);
    execAndReset(statement, cur_char_ptr);
}

void
data::SQLConnection::execAndReset(char* a_statement_ptr,
                                  char* a_cur_char_ptr) noexcept
{
    m_db_conn.exec(a_statement_ptr);
    m_db_conn.closeStatement();
    a_cur_char_ptr    = a_statement_ptr;
    a_cur_char_ptr[0] = 0;
}
