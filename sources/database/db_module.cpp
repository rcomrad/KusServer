#include "db_module.hpp"

#include "kernel/framework/include_me.hpp"

#include "credentials.hpp"
#include "mass_executor.hpp"

namespace database
{

auto module_name = "database";
REG_MODULE(module_name, DBModule);

DBModule::DBModule() : core::Module(module_name)
{
    registrateBaseCommand("db_add_cred",
                          "Creates a module with the specified name.",
                          "[module_name]...");
    KERNEL.listenCommand("db_add_cred",
                         core::StateStorage::StateType::RESET_ARGS |
                             core::StateStorage::StateType::RESET_VARS);
    registrateBaseCommand("db_dump", "Dump database content",
                          "[tablename], ...");
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
    // TODO: THROW/ASSERT
    a_command.noVars().argCount(Credentials::COUNT);

    Credentials cred(a_command.arguments);
    m_con_pools.emplace(cred.user, cred);

    LOG_CMD("Modules created successfully.");
}

void
DBModule::dbDump(core::Command& a_command)
{
    // TODO: THROW/ASSERT
    a_command.noVars();
    auto& pool = getConnectionPool("postgres");
    auto conn  = pool.get();
    auto& exec = MassExecutor::getInstance();

    std::string result;
    if (a_command.arguments.empty())
    {
        result = exec.dumpAll(conn);
        if (result.empty())
        {
            result = "DB is empty";
        }
    }
    else
    {
        result = "Sorry, we haven't done this function";
    }

    LOG_CMD("%s", result);
}

} // namespace database
