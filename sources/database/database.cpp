#include "database.hpp"

// TRIGGER_SINGLETON_ENTRY_POINT(data::Database)

data::Database::Database() noexcept : core::Module("database")
{
}

void
data::Database::initialize() noexcept
{
    // DBCredentials temp("journal_db", "rcomrad", "123", "127.0.0.1", "5432");
    // getInstance().m_db_connections.emplace_back(temp);
    m_db_connections.emplace_back(0, 0);
}

data::DatabaseConnection&
data::Database::getNonstatic(word_t a_user_id) noexcept
{
    return m_db_connections[0];
}

void
data::Database::putNonstatic(DatabaseConnection& a_conn) noexcept
{
}
