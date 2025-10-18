#pragma once

#include <memory>
#include <semaphore>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "credentials.hpp"
#include "sql_connection.hpp"

namespace database
{

class ConnectionPool
{
public:
    ConnectionPool(const Credentials& a_credentials,
                   size_t a_count = 1) ;

    SQLConnection& get();
    void put(SQLConnection& a_sql_conn);

    // void setConnectionCount(size_t a_count) ;

private:
    const Credentials m_credentials; // All connections save copy of user name

    int m_total_count;
    std::counting_semaphore<5> m_avaliable_count;
    std::mutex m_avaluable_mutex;
    std::vector<SQLConnection*> m_avaluable;

    std::unordered_map<SQLConnection*, std::unique_ptr<SQLConnection>>
        m_storage;
};

} // namespace data
