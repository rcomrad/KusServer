#include "db_module.hpp"

#include "kernel/framework/include_me.hpp"

#include "credentials.hpp"

namespace database
{

auto module_name = "database";
REG_MODULE(module_name, DBModule);

DBModule::DBModule() : core::Module(module_name)
{
    registrateBaseCommand("db_add_cred",
                          "Creates a module with the specified name.",
                          "[module_name]...");
}

void
DBModule::initialize()
{
}

ConnectionPool&
DBModule::getConnectionPool(const std::string& a_name)
{
    auto it = m_con_pools.find(a_name);
    if (it == m_con_pools.end())
    {
        THROW("No connection pool");
    }
    return it->second;
}

void
DBModule::dbAddCred(core::Command& a_command)
{
    a_command.noVars().argCount(Credentials::COUNT);

    Credentials cred(a_command.arguments);
    m_con_pools.emplace(cred.user, cred);

    LOG_CMD("Modules created successfully.");
}

} // namespace database
