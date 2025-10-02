#pragma once

#include "kernel/utility/string/string_builder.hpp"

#include "credentials.hpp"
#include "postgresql.hpp"
#include "table_specific.hpp"

namespace database
{

class SQLConnection
{
public:
    SQLConnection(const Credentials& a_cred);

    void createEnvironment(const Credentials& a_cred);
    void createTable(std::string_view a_table_name,
                     std::string_view a_table_body);
    void deleteTable(std::string_view a_table_name);

    template <typename TableType>
    int insert(const TableType& a_data);

    template <typename TableType>
    TableType select(std::string_view a_condition = "");

    // template <typename TableType>
    // std::vector<TableType> selectAll(std::string_view a_condition = "");

private:
    PostgreSQL m_db_conn;
    std::string m_user_name;

    void execAndClose(std::string_view a_str);
    void execAndClose(util::StringBuilder& a_sb);
};

template <typename TableType>
int
SQLConnection::insert(const TableType& a_data)
{
    TableSpecific<TableType> specific;
    util::StringBuilder sb;

    sb.add("INSERT INTO ");
    sb.add(specific.getTableName());
    sb.add(" VALUES(");
    specific.insert(sb, a_data);
    sb.add(")RETURNING id;");

    auto statement_ptr = sb.collapse();
    auto raw_statement = statement_ptr.get();
    m_db_conn.exec(raw_statement);
    m_db_conn.step();
    int result = m_db_conn.getInt(0);
    m_db_conn.closeStatement();

    return result;
}

// template <typename TableType>
// TableType
// SQLConnection::selectAll(std::string_view a_condition = "")
// {
//     TableSpecific<TableType> specific;
//     util::StringBuilder sb;

//     sb.add("SELECT * FROM ");
//     sb.add(specific.getTableName());
//     if (!a_condition.empty())
//     {
//         sb.add(" WHERE ");
//         sb.add(a_condition);
//     }
//     sb.add(";");

//     auto statement_ptr = sb.collapse();
//     auto raw_statement = statement_ptr.get();
//     m_db_conn.exec(raw_statement);
//     m_db_conn.step();

//     TableType result;
//     specific.select(m_db_conn, result);
//     return result;
// }

template <typename TableType>
TableType
SQLConnection::select(std::string_view a_condition)
{
    TableSpecific<TableType> specific;
    util::StringBuilder sb;

    sb.add("SELECT * FROM ");
    sb.add(specific.getTableName());
    if (!a_condition.empty())
    {
        sb.add(" WHERE ");
        sb.add(a_condition);
    }
    sb.add(";");

    auto statement_ptr = sb.collapse();
    auto raw_statement = statement_ptr.get();
    m_db_conn.exec(raw_statement);
    m_db_conn.step();

    TableType result;
    specific.select(m_db_conn, result);
    return result;
}

} // namespace database
