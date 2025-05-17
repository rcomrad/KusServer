#include "connection_pool.hpp"

data::ConnectionPool::ConnectionPool(uint16_t aPoolSize,
                                     const ConnectionType& aType) noexcept
    : mPoolSize(aPoolSize)
{
    mGetMutex.lock();
    create(aPoolSize, aType);
}

std::optional<data::DatabaseConnection>
data::ConnectionPool::tryGetConnection() noexcept
{
    // std::cout << "before_lock_size: " << mConnections.size() << "\n";

    const std::lock_guard<std::mutex> lock(mGetMutex);
    const std::lock_guard<std::mutex> lock2(mPushMutex);
    std::optional<data::DatabaseConnection> res = {};
    if (!mConnections.empty())
    {
        res.emplace(std::move(mConnections.back()));
        mConnections.pop_back();
    }
    return res;
}

void
data::ConnectionPool::returnConnectionToPool(
    data::DatabaseConnection&& aConnection) noexcept
{
    const std::lock_guard<std::mutex> lock(mPushMutex);
    mConnections.emplace_back(std::move(aConnection));
}

void
data::ConnectionPool::destroy() noexcept
{
    mGetMutex.lock();
    uint16_t cnt = 0;
    while (cnt < mPoolSize)
    {
        mPushMutex.lock();
        if (!mConnections.empty())
        {
            mConnections.pop_back();
            ++cnt;
        }
        mPushMutex.unlock();
    }
}

void
data::ConnectionPool::create(uint16_t aPoolSize,
                             const ConnectionType& aType) noexcept
{
    for (size_t i = 0; i < aPoolSize; ++i)
    {
        mConnections.emplace_back(DatabaseConnection(aType));
    }
    mGetMutex.unlock();
}
