#pragma once

#include "core/holy_trinity.hpp"

#include "sql_connection.hpp"

namespace data
{

class DatabaseConnection
{
public:
    DatabaseConnection(const DatabaseConnection&) noexcept            = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) noexcept = delete;
    DatabaseConnection(DatabaseConnection&& other) noexcept;
    DatabaseConnection& operator=(DatabaseConnection&& other) noexcept;

    DatabaseConnection(SQLConnection* a_sql_conn, size_t a_pool_id) noexcept;
    ~DatabaseConnection();

    void populateDatabse() noexcept;
    void release() noexcept;

    size_t getPollId() const noexcept;
    bool hasValue() const noexcept;

private:
    size_t m_pool_id;
    SQLConnection* m_sql_conn;
};

} // namespace data
