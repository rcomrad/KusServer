#ifndef CONNECTION_POOL_HPP
#define CONNECTION_POOL_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <optional>

#include "database_connection.hpp"

//--------------------------------------------------------------------------------

namespace data
{
class ConnectionPool
{
public:
    // ConnectionPool() noexcept = default;
    ConnectionPool(uint16_t aPoolSize, const ConnectionType& aType) noexcept;

    ConnectionPool(ConnectionPool&& other) noexcept            = default;
    ConnectionPool& operator=(ConnectionPool&& other) noexcept = default;

    std::optional<DatabaseConnection> tryGetConnection() noexcept;
    void returnConnectionToPool(
        data::DatabaseConnection&& aConnection) noexcept;

    void destroy() noexcept;
    void create(uint16_t aPoolSize, const ConnectionType& aType) noexcept;

private:
    uint16_t mPoolSize;
    std::mutex mGetMutex;
    std::mutex mPushMutex;
    std::vector<DatabaseConnection> mConnections;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !CONNECTION_POOL_HPP
