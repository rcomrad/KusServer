#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <array>
#include <mutex>
#include <optional>

#include "connection_pool.hpp"

//--------------------------------------------------------------------------------

namespace data
{
class ConnectionManager;

struct SmartConnection
{
    DatabaseConnection val;
    ~SmartConnection();

private:
    friend ConnectionManager;

    SmartConnection(const ConnectionType& aConnectionType) noexcept;

    ConnectionType mConnectionType;
};

class ConnectionManager
{
public:
    static SmartConnection getUserConnection() noexcept;
    static SmartConnection getAdminConnection() noexcept;

    static void turnOn() noexcept;
    static void turnOff() noexcept;

private:
    friend SmartConnection;

    std::array<ConnectionPool, 2> mConnectionPools;

    ConnectionManager() noexcept;
    static ConnectionManager& getInstance() noexcept;

    data::DatabaseConnection getConnection(
        const data::ConnectionType& aType) noexcept;
    void returnConnection(const data::ConnectionType& aType,
                          data::DatabaseConnection&& aConnection) noexcept;
};
} // namespace data

//--------------------------------------------------------------------------------

#endif // !CONNECTION_MANAGER_HPP
