#pragma once

#include <mutex>
#include <optional>
#include <semaphore>
#include <shared_mutex>
#include <string>
#include <unordered_set>
#include <vector>

#include "core/logging/table_storage.hpp"

#include "database_connection.hpp"

#include "utility/type/lifecycle_manager.hpp"

#include "credentials.hpp"
#include "internal_connection.hpp"

enum
{
    MAX_CONNECTIONS_COUNT = 5
};

using PoolSemaphore = std::counting_semaphore<MAX_CONNECTIONS_COUNT>;

namespace data
{

class ConnectionPool
{
public:
    HOLY_TRINITY_NOCOPY(ConnectionPool);

    static bool create(
        util::LifecycleManager<ConnectionPool>& a_poll_addr,
        const std::vector<std::string_view>& a_credentials_array) noexcept;

    InternalConnection& get() noexcept;
    void put(InternalConnection& a_sql_conn) noexcept;

    void setConnectionCount(size_t a_count) noexcept;

private:
    int m_cur_conn_count;
    int m_max_conn_count;
    Credentials m_credentials;
    // TODO: table print vector size
    std::vector<InternalConnection> m_connections;

    std::shared_mutex m_resize_mutex;
    std::vector<InternalConnection&> m_available_conn;
    util::LifecycleManager<PoolSemaphore> m_available_semaphore;

    static std::unordered_set<std::string> m_all_cred_combined;

    TABLE_REGISTER_HPP(ConnectionPool,
                       .addCol(obj.m_cur_conn_count, obj.m_max_conn_count)
                           .addRow(obj.m_credentials));

    ConnectionPool(
        const std::vector<std::string_view>& a_credentials_array) noexcept;
};

} // namespace data
