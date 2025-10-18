#include "connection_pool.hpp"

namespace database
{

//-----------------------------------------------------------------------------
// Connection pool creation
//-----------------------------------------------------------------------------

ConnectionPool::ConnectionPool(const Credentials& a_credentials,
                                     size_t a_count)
    : m_credentials(a_credentials),
      m_total_count(a_count),
      m_avaliable_count(a_count)
{
    m_avaluable.reserve(m_total_count);
    for (int i = 0; i < m_total_count; ++i)
    {
        auto temp   = std::make_unique<SQLConnection>(m_credentials);
        auto raw_ptr = temp.get();

        m_storage.emplace(raw_ptr, std::move(temp));
        m_avaluable.emplace_back(raw_ptr);
    }
}

//-----------------------------------------------------------------------------
// Database obtaining
//-----------------------------------------------------------------------------

SQLConnection&
ConnectionPool::get() 
{
    m_avaliable_count.acquire();
    const std::lock_guard lock(m_avaluable_mutex);
    auto result = m_avaluable.back();
    m_avaluable.pop_back();
    return *result;
}

void
ConnectionPool::put(SQLConnection& a_sql_conn) 
{
    const std::lock_guard lock(m_avaluable_mutex);
    m_avaluable.emplace_back(&a_sql_conn);
    m_avaliable_count.release();
}

}
