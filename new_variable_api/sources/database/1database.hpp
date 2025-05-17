// #pragma once

// //--------------------------------------------------------------------------------

// #include "utility/common/holy_trinity.hpp"
// #include "core/module.hpp"

// #include "database_connection.hpp"

// #include "sql_connection.hpp"

// //--------------------------------------------------------------------------------

// namespace data
// {

// class Database : public core::Module
// {
// public:
//     HOLY_TRINITY_SINGLETON(Database);

//     void initialize() noexcept override;

//     SINGL_RET_METHOD(SQLConnection&, get, (word_t a_user_id));
//     SINGL_VOID_METHOD(put, (SQLConnection * a_conn));

// protected:
//     void commandSetup() noexcept override;

// private:
//     std::vector<SQLConnection> m_db_connections;

//     Database() noexcept;

//     COMMAND_HANDLER_NONSTATIC(showConncetions);
// };

// } // namespace data
