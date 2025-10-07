#include "sql_connection.hpp"

#include "connection_pool.hpp"
#include "mass_executor.hpp"

namespace database
{

SQLConnection::SQLConnection(PostgreSQL& a_psql,
                             const std::string& a_user_name,
                             ConnectionPool* a_parent)
    : m_db_conn(a_psql), m_user_name(a_user_name), m_parent(a_parent)
{
}

SQLConnection::~SQLConnection()
{
    m_parent->put(m_db_conn);
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

// std::string
// SQLConnection::dumpAll()
// {
//     return MassExecutor::getInstance().dumpAll(*this);
// }

// void
// SQLConnection::load(std::string& a_data)
// {
//     return MassExecutor::getInstance().load(*this, a_data);
// }

} // namespace database
