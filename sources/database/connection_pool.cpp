#include "connection_pool.hpp"

#include <mutex>
#include <unordered_set>

#include "core/holy_trinity.hpp"
#include "core/logging.hpp"

namespace
{
struct CredentialsHashStorage
{
public:
    HOLY_TRINITY_SINGLETON(CredentialsHashStorage);

    std::unordered_set<uint64_t> storage;
    std::mutex mutex;

private:
    CredentialsHashStorage() = default;
};
} // namespace

SINGLETON_DEFINITOR(, CredentialsHashStorage)

data::ConnectionPool::ConnectionPool(uint64_t a_hash,
                                     Credentials&& a_credentials) noexcept
    : m_hash(a_hash),
      m_credentials(std::move(a_credentials)),
      m_max_conn_count(0)
{
}

data::ConnectionPool::ConnectionPool(ConnectionPool&& other) noexcept
    : m_credentials("", "", "", "", "", "")
{
    *this = std::move(other);
}

data::ConnectionPool&
data::ConnectionPool::operator=(ConnectionPool&& other) noexcept
{
    m_hash           = other.m_hash;
    m_max_conn_count = other.m_max_conn_count;
    m_credentials    = std::move(other.m_credentials);
    m_connections    = std::move(m_connections);

    other.m_hash = 0;

    return *this;
}

data::ConnectionPool::~ConnectionPool()
{
    auto& hash_storage = CredentialsHashStorage::getInstance();
    // const std::lock_guard<std::mutex> lock(hash_storage.mutex);
    hash_storage.storage.erase(m_hash);
}

std::optional<data::ConnectionPool>
data::ConnectionPool::create(
    const std::vector<std::string>& a_credentials_array) noexcept
{
    std::optional<ConnectionPool> result;

    Credentials credentials(
        a_credentials_array[0].c_str(), a_credentials_array[1].c_str(),
        a_credentials_array[2].c_str(), a_credentials_array[3].c_str(),
        a_credentials_array[4].c_str(), a_credentials_array[5].c_str());
    auto hash = credentials.calculateHash();

    auto& hash_storage = CredentialsHashStorage::getInstance();
    // const std::lock_guard<std::mutex> lock(hash_storage.mutex);
    if (!hash_storage.storage.count(hash))
    {
        ConnectionPool pool(hash, std::move(credentials));
        hash_storage.storage.insert(hash);
        result = std::move(pool);
    }
    else
    {
        LOG_ERROR("Hash '%lu' already present", hash);
    }

    return result;
}

data::DatabaseConnection
data::ConnectionPool::get(size_t a_pool_id) noexcept
{
    if (m_connections.size() < 1)
    {
        m_connections.emplace_back(m_credentials);
    }
    return DatabaseConnection(&m_connections[0], a_pool_id);
}

void
data::ConnectionPool::put(SQLConnection* a_sql_conn) noexcept
{
}

void
data::ConnectionPool::printData(char** a_ptr,
                                core::TablePrintHelper& a_table,
                                bool a_if_add_poll) const noexcept
{
    if (a_if_add_poll)
    {
        a_table.printData(a_ptr, m_hash);
        a_table.printData(a_ptr, m_connections.size());
        a_table.printData(a_ptr, m_max_conn_count);
    }
    m_credentials.printData(a_ptr, a_table);
}

void
data::ConnectionPool::configurateTable(core::TablePrintHelper& a_table,
                                       bool a_if_add_poll) noexcept
{
    if (a_if_add_poll)
    {
        PUSH_COMBINED_COLUMN(ConnectionPool, m_hash, 18, "hash");
        PUSH_COMBINED_COLUMN(ConnectionPool, m_connections.size(), 3, "cur");
        PUSH_COMBINED_COLUMN(ConnectionPool, m_max_conn_count, 3, "max");
    }
    Credentials::configurateTable(a_table);
}

void
data::ConnectionPool::dumpCredentialsToFIle(
    fs::FileWrite& a_file) const noexcept
{
    m_credentials.dumpCredentialsToFIle(a_file);
}
