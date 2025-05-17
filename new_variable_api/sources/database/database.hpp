// #pragma once

// #include <set>
// #include <vector>

// #include "core/command/command.hpp"
// #include "core/command/register.hpp"
// #include "core/module/module.hpp"
// #include "core/logging/table_print_helper.hpp"

// #include "utility/common/holy_trinity.hpp"
// #include "utility/type/base.hpp"

// #include "connection_pool.hpp"

// namespace data
// {

// class Database : public core::Module
// {
// public:
//     HOLY_TRINITY_SINGLETON(Database);

//     SINGL_RET_METHOD(DatabaseConnection, getConnection, (size_t a_pool_id));
//     SINGL_VOID_METHOD(putConnection,
//                       (SQLConnection * a_sql_conn, size_t a_pool_id));

//     void initialize() noexcept override;

// protected:
//     void commandSetup() const noexcept override;

// private:
//     std::vector<ConnectionPool> m_conn_storage;
//     DatabaseConnection m_obtained_connection;

//     Database() noexcept;

//     bool addCredentials(const char* name,
//                         const char* user,
//                         const char* password,
//                         const char* hostaddr,
//                         const char* port,
//                         const char* shame) noexcept;
//     bool removeCredentials(size_t a_num) noexcept;
//     void dumpCredentialsToFIle() const noexcept;

//     COMMAND_HANDLER_NONSTATIC(addCredentials);
//     COMMAND_HANDLER_NONSTATIC(addBaseCredentials);
//     COMMAND_HANDLER_NONSTATIC(removeCredentials);
//     COMMAND_HANDLER_NONSTATIC(showCredentials);

//     COMMAND_HANDLER_NONSTATIC(obtainConnection);
//     COMMAND_HANDLER_NONSTATIC(returnConnection);
//     COMMAND_HANDLER_NONSTATIC(currentConnection);
//     COMMAND_HANDLER_NONSTATIC(executeConnection);

//     static core::TablePrintHelper configurateShowTable() noexcept;
//     static core::TablePrintHelper configurateCurTable() noexcept;
// };

// } // namespace data
