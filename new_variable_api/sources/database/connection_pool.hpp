// #pragma once

// #include <optional>
// #include <string>
// #include <vector>

// #include "core/logging/table_print_helper.hpp"

// #include "database_connection.hpp"

// #include "credentials.hpp"
// #include "sql_connection.hpp"

// namespace data
// {

// class ConnectionPool
// {
// public:
//     // TODO: remove
//     ConnectionPool() noexcept = default;

//     ConnectionPool(const ConnectionPool&) noexcept            = delete;
//     ConnectionPool& operator=(const ConnectionPool&) noexcept = delete;
//     ConnectionPool(ConnectionPool&& other) noexcept;
//     ConnectionPool& operator=(ConnectionPool&& other) noexcept;

//     // TODO: implement destruction
//     ~ConnectionPool();

//     // TODO: RVO check
//     static std::optional<ConnectionPool> create(
//         const std::vector<std::string>& a_credentials_array) noexcept;

//     DatabaseConnection get(size_t a_pool_id) noexcept;
//     void put(SQLConnection* a_sql_conn) noexcept;

//     const Credentials& getCredentials() const noexcept;

//     void printData(char** a_ptr,
//                    core::TablePrintHelper& table,
//                    bool a_if_add_poll) const noexcept;
//     static void configurateTable(core::TablePrintHelper& table,
//                                  bool a_if_add_poll) noexcept;

//     void dumpCredentialsToFIle(fs::FileWrite& a_file) const noexcept;

// private:
//     uint64_t m_hash;
//     Credentials m_credentials;
//     int m_max_conn_count;
//     std::vector<SQLConnection> m_connections;

//     ConnectionPool(uint64_t a_hash, Credentials&& a_credentials) noexcept;
// };

// } // namespace data
