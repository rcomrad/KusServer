// #include "database.hpp"

// TRIGGER_SINGLETON_ENTRY_POINT(data::Database)

// data::Database::Database() noexcept : core::Module("database")
// {
// }

// void
// data::Database::initialize() noexcept
// {
//     // m_db_connections.emplace_back(0, 0);
// }

// data::SQLConnection&
// data::Database::getNonstatic(word_t a_user_id) noexcept
// {
//     return m_db_connections[0];
// }

// void
// data::Database::putNonstatic(SQLConnection* a_conn) noexcept
// {
// }

// void
// data::Database::commandSetup() noexcept
// {
//     a_command_data.emplace_back("add_log_info");
// }
