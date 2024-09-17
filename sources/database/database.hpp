#pragma once

#include <vector>

#include "core/command/command_extend.hpp"
#include "core/module/module.hpp"

#include "utility/common/holy_trinity.hpp"
#include "utility/type/lifecycle_manager.hpp"

#include "connection_pool.hpp"

namespace data
{

class Database : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Database);

    SINGL_RET_METHOD(DatabaseConnection, getConnection, (size_t a_pool_id));
    SINGL_VOID_METHOD(putConnection,
                      (InternalConnection & a_sql_conn, size_t a_pool_id));

protected:
    void commandSetup() const noexcept override;

private:
    std::vector<util::LifecycleManager<ConnectionPool>> m_conn_storage;
    util::LifecycleManager<DatabaseConnection> m_obtained_connection;
    // DatabaseConnection* m_obtained_connection;
    // bool m_has_obtained_connection;
    // m_obtained_connection;

    Database() noexcept;

    bool addCredentials(const char* name,
                        const char* user,
                        const char* password,
                        const char* hostaddr,
                        const char* port,
                        const char* shame) noexcept;
    bool removeCredentials(size_t a_num) noexcept;

    void clearObtainedConnection() noexcept;

    COMMAND_HANDLER_NONSTATIC(addCredentials);
    COMMAND_HANDLER_NONSTATIC(addBaseCredentials);
    COMMAND_HANDLER_NONSTATIC(removeCredentials);
    COMMAND_HANDLER_NONSTATIC(showCredentials);

    COMMAND_HANDLER_NONSTATIC(obtainConnection);
    COMMAND_HANDLER_NONSTATIC(returnConnection);
    COMMAND_HANDLER_NONSTATIC(currentConnection);
    COMMAND_HANDLER_NONSTATIC(executeConnection);
};

} // namespace data
