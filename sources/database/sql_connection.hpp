#pragma once

#include <format>
#include <optional>

#include "kernel/utility/string/string_builder.hpp"

#include "postgresql.hpp"

namespace database
{

class SQLConnection
{
public:
    SQLConnection(const Credentials& a_cred);

    void createEnvironment(const Credentials& a_cred);

    template <typename TableType>
    int insert(const TableType& a_data);
    template <typename TableType>
    std::optional<TableType> select(std::string_view a_condition = "");
    template <typename TableType>
    TableType selectUnsafe(std::string_view a_condition = "");

    template <typename TableType>
    std::vector<TableType> selectArray(std::string_view a_condition = "");

    template <typename TableType>
    void createTable();
    template <typename TableType>
    void deleteTable();

    void clear();
    template <typename TableType>
    std::string dump();
    std::string dumpAll();

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
    util::StringBuilder sb;

    sb.add("INSERT INTO ");
    sb.add(a_data.getTableName());
    sb.add(" VALUES(");
    a_data.insert(sb);
    sb.add(")RETURNING id;");

    auto statement_ptr = sb.collapse();
    auto raw_statement = statement_ptr.get();
    m_db_conn.exec(raw_statement);
    m_db_conn.step();
    int result = m_db_conn.getInt(0);
    m_db_conn.closeStatement();

    return result;
}

template <typename TableType>
std::optional<TableType>
SQLConnection::select(std::string_view a_condition)
{
    util::StringBuilder sb;

    sb.add("SELECT * FROM ");
    sb.add(TableType::getTableName());
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

    std::optional<TableType> result;
    if (m_db_conn.hasData())
    {
        result         = TableType();
        TableType& ref = result.value();
        ref.select(m_db_conn);
    }
    return result;
}

template <typename TableType>
TableType
SQLConnection::selectUnsafe(std::string_view a_condition)
{
    auto result = select<TableType>(a_condition);
    return result.value();
}

template <typename TableType>
std::vector<TableType>
SQLConnection::selectArray(std::string_view a_condition)
{
    util::StringBuilder sb;

    sb.add("SELECT * FROM ");
    sb.add(TableType::getTableName());
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

    std::vector<TableType> result;
    while (m_db_conn.hasData())
    {
        auto& ref = result.emplace_back();
        ref.select(m_db_conn);
        m_db_conn.step();
    }
    return result;
}

template <typename TableType>
void
SQLConnection::createTable()
{
    execAndClose(std::format(
        "CREATE TABLE IF NOT EXISTS {} (id integer GENERATED ALWAYS AS "
        "IDENTITY PRIMARY KEY, {});",
        TableType::getTableName(), TableType::getTableInfo()));

    execAndClose(std::format("ALTER TABLE {} OWNER TO {};",
                             TableType::getTableName(), m_user_name));
}

template <typename TableType>
void
SQLConnection::deleteTable()
{
    execAndClose(
        std::format("DROP TABLE IF EXISTS {};", TableType::getTableName()));
}

// TODO: string builder
template <typename TableType>
std::string
SQLConnection::dump()
{
    std::string result = std::format("TABLE {}\n", TableType::getTableName());
    auto arr           = selectArray<TableType>();
    for (auto& i : arr)
    {
        result += i.dump();
        result.push_back('\n');
    }
    result += "END\n";
    return result;
}

} // namespace database
