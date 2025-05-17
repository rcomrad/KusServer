#include "connection_manager.hpp"

#include "domain/variable_storage.hpp"

//--------------------------------------------------------------------------------

data::SmartConnection::SmartConnection(
    const ConnectionType& aConnectionType) noexcept
    : val(data::ConnectionManager::getInstance().getConnection(
          aConnectionType)),
      mConnectionType(aConnectionType)
{
}

data::SmartConnection::~SmartConnection() noexcept
{
    data::ConnectionManager::getInstance().returnConnection(mConnectionType,
                                                            std::move(val));
}

//--------------------------------------------------------------------------------

data::SmartConnection
data::ConnectionManager::getUserConnection() noexcept
{
    return SmartConnection(data::ConnectionType::USER);
}

data::SmartConnection
data::ConnectionManager::getAdminConnection() noexcept
{

    return SmartConnection(data::ConnectionType::ADMIN);
}

//--------------------------------------------------------------------------------

data::ConnectionManager::ConnectionManager() noexcept
    : mConnectionPools{ConnectionPool(1, data::ConnectionType::ADMIN),
                       ConnectionPool(dom::VariableStorage::touchInt(
                                          "database_connection_count", 3),
                                      data::ConnectionType::USER)}
{
    // auto& state              = core::ProgramState::getInstance();
    // uint16_t connectionCount = state.getDatabaseConnectionCount();

    // mConnectionPools[0] =
    //     std::move(ConnectionPool(1, data::ConnectionType::ADMIN));
    // mConnectionPools[1] =
    //     std::move(ConnectionPool(connectionCount,
    //     data::ConnectionType::USER));
}

data::ConnectionManager&
data::ConnectionManager::getInstance() noexcept
{
    static ConnectionManager instance;
    return instance;
}

//--------------------------------------------------------------------------------

data::DatabaseConnection
data::ConnectionManager::getConnection(
    const data::ConnectionType& aType) noexcept
{
    // TODO: gnu can't make rvo here for some reason and failse!
    //  std::optional<DatabaseConnection> temp = {};
    //  while (!temp.has_value())
    //  {
    //      temp = mConnectionPools[int(aType)].tryGetConnection();
    //  }

    while (true)
    {
        std::optional<DatabaseConnection> temp =
            mConnectionPools[int(aType)].tryGetConnection();
        if (temp.has_value())
        {
            data::DatabaseConnection res = std::move(temp.value());
            return res;
        }
    }
}

void
data::ConnectionManager::returnConnection(
    const data::ConnectionType& aType,
    data::DatabaseConnection&& aConnection) noexcept
{
    mConnectionPools[int(aType)].returnConnectionToPool(std::move(aConnection));
}

//--------------------------------------------------------------------------------

void
data::ConnectionManager::turnOn() noexcept
{
    getInstance().mConnectionPools[1].create(
        dom::VariableStorage::touchInt("database_connection_count", 3),
        data::ConnectionType::USER);
}

void
data::ConnectionManager::turnOff() noexcept
{
    getInstance().mConnectionPools[1].destroy();
}
