#pragma once

#include "core/holy_trinity.hpp"

#include "sql_connection.hpp"

namespace data
{

class DatabaseConnection
{
public:
    HOLY_TRINITY_NOCOPY(DatabaseConnection);
    DatabaseConnection(word_t a_credentials_id,
                       word_t a_connection_id) noexcept;

    void populateDatabse() noexcept;
    void release();

    const word_t m_connection_id;

private:
    SQLConnection m_sql_conn;
};

} // namespace data
