#pragma once

#include <unordered_map>

#include "kernel/framework/module/include_me.hpp"

#include "connection_pool.hpp"

namespace database
{

class DBModule : public core::Module, public core::CommandCaller
{
public:
    DBModule();

    ConnectionPool& getConnectionPool(const std::string& a_name);

protected:
    void initialize() override;

private:
    std::unordered_map<std::string, ConnectionPool> m_con_pools;

    COMMAND_HANDLER(dbAddCred, 0);
};

} // namespace database
