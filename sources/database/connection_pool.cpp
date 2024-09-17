#include "connection_pool.hpp"

#include <mutex>
#include <unordered_set>

#include "core/logging/logging.hpp"

#include "utility/common/holy_trinity.hpp"

//-----------------------------------------------------------------------------
// Connection pool creation
//-----------------------------------------------------------------------------

std::unordered_set<std::string> data::ConnectionPool::m_all_cred_combined;

data::ConnectionPool::ConnectionPool(
    const std::vector<std::string_view>& a_credentials_array) noexcept
    : m_credentials(a_credentials_array),
      m_cur_conn_count(0),
      m_max_conn_count(0)
{
    // m_available_conn.reserve(MAX_CONNECTIONS_COUNT);
}

bool
data::ConnectionPool::create(
    util::LifecycleManager<ConnectionPool>& a_poll_addr,
    const std::vector<std::string_view>& a_credentials_array) noexcept
{
    bool result = false;
    a_poll_addr.create(a_credentials_array);
    auto combined = a_poll_addr.obj.m_credentials.getCombined();
    if (!m_all_cred_combined.count(combined))
    {
        a_poll_addr.obj.setConnectionCount(1);
        m_all_cred_combined.insert(combined);
        result = true;
    }
    return result;
}

//-----------------------------------------------------------------------------
// Database obtaining
//-----------------------------------------------------------------------------

data::InternalConnection&
data::ConnectionPool::get() noexcept
{
    std::shared_lock lock(m_resize_mutex);
    m_available_semaphore.obj.acquire();
    auto& result = m_available_conn.back();
    m_available_conn.pop_back();
    return result;
}

void
data::ConnectionPool::put(InternalConnection& a_sql_conn) noexcept
{
    std::shared_lock lock(m_resize_mutex);
    m_available_conn.emplace_back(a_sql_conn);
    m_available_semaphore.obj.release();
}

//-----------------------------------------------------------------------------
// Connection resizers
//-----------------------------------------------------------------------------

void
data::ConnectionPool::setConnectionCount(size_t a_count) noexcept
{
    std::unique_lock lock(m_resize_mutex);

    for (int i = 0; i < m_cur_conn_count; ++i)
    {
        m_available_semaphore.obj.acquire();
    }
    m_available_semaphore.destroy();

    m_cur_conn_count = a_count;
    m_connections.resize(m_cur_conn_count, m_credentials);

    m_available_conn.clear();
    for (auto& i : m_connections)
    {
        m_available_conn.emplace_back(i);
    }

    m_available_semaphore.create(m_cur_conn_count);
    for (int i = 0; i < m_cur_conn_count; ++i)
    {
        m_available_semaphore.obj.release();
    }
}
