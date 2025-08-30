#include "sql_connection.hpp"

#include <format>

namespace database
{

SQLConnection::SQLConnection(const Credentials& a_cred)
    : m_db_conn(a_cred), m_user_name(a_cred.user)
{
}

void
SQLConnection::createEnvironment(const Credentials& a_cred)
{
    execAndClose(std::format("CREATE DATABASE {} WITH ENCODING 'ISO_8859_5' "
                             "LC_COLLATE='C' LC_CTYPE='C' TEMPLATE=template0;",
                             a_cred.db_name));

    execAndClose(std::format("CREATE USER {} WITH PASSWORD {};", a_cred.user,
                             a_cred.password));

    execAndClose(std::format(
        "ALTER ROLE {} SET client_encoding TO 'ISO_8859_5';", a_cred.user));
    execAndClose(
        std::format("ALTER ROLE {} SET timezone TO 'UTC+3';", a_cred.user));

    execAndClose(std::format("GRANT ALL PRIVILEGES ON DATABASE {} TO {} ;",
                             a_cred.db_name, a_cred.user));
}

void
SQLConnection::createTable(std::string_view a_table_name,
                           std::string_view a_table_body)
{
    execAndClose(std::format(
        "CREATE TABLE IF NOT EXISTS {} (id integer GENERATED ALWAYS AS "
        "IDENTITY PRIMARY KEY, {});",
        a_table_name, a_table_body));

    execAndClose(
        std::format("ALTER TABLE {} OWNER TO {};", a_table_name, m_user_name));
}

void
SQLConnection::deleteTable(std::string_view a_table_name)
{
    auto statement = std::format("DROP TABLE IF EXISTS {};", a_table_name);
    execAndClose(statement);
}

void
SQLConnection::execAndClose(std::string_view a_str)
{
    m_db_conn.exec(a_str.data());
    m_db_conn.closeStatement();
}

void
SQLConnection::execAndClose(util::StringBuilder& a_sb)
{
    execAndClose(a_sb.collapse().get());
}

} // namespace database
