#include "database.hpp"

#include <cstring>

#include "core/logging/table_printer.hpp"

//-----------------------------------------------------------------------------

#define CREDENTIALS_FOLDER "bin"
#define CREDENTIALS_FILE   "db_credentials.txt"

//-----------------------------------------------------------------------------
// Module setup
//-----------------------------------------------------------------------------

SINGLETON_DEFINITOR(data, Database);

data::Database::Database() noexcept : Module("database")
{
}

data::DatabaseConnection
data::Database::getConnectionNonstatic(size_t a_pool_id) noexcept
{
    // TODO: check?
    return DatabaseConnection(m_conn_storage[a_pool_id].obj.get(), a_pool_id);
}

void
data::Database::putConnectionNonstatic(InternalConnection& a_sql_conn,
                                       size_t a_pool_id) noexcept
{
    m_conn_storage[a_pool_id].obj.put(a_sql_conn);
}

void
data::Database::commandSetup() const noexcept
{
    registerCommand("data_add", addCredentials,
                    "Adding database credentials to the repository.",
                    "name1 name2 name3");
    registerCommand("data_remove", removeCredentials,
                    "Deleting database credentials from the repository.",
                    "credential_number");
    registerCommand("data_show", showCredentials,
                    "Show the database credentials stored in the repository.");

    registerCommand(
        "conn_obtain", obtainConnection,
        "Obtain database connection from the repository for console usage.",
        "credential_number");
    registerCommand("conn_return", returnConnection,
                    "Release obtained database connection.");
    registerCommand("conn_cur", currentConnection,
                    "Print obtained database connection credentials.");
    registerCommand(
        "conn_exec", currentConnection,
        "Use obtained connection to execute specified database command.",
        "command");

    setCommandStateType("data_add",
                        core::StateStorage::StateType::COMMAND_ARGS);
}

//-----------------------------------------------------------------------------
// Add/Remove connection (credential) commands
//-----------------------------------------------------------------------------

void
data::Database::addCredentialsNonstatic(core::CommandExtend& a_command) noexcept
{
    // CMD_ASSERT(argCount({2, 6}).noVars());
    CMD_ASSERT(argCount(6).noVars());

    if (ConnectionPool::create(m_conn_storage.emplace_back(),
                               a_command.arguments))
    {
        PRINT_CMD_MSG(a_command, "Credentials successfully added");
    }
    else
    {
        m_conn_storage.pop_back();
        PRINT_CMD_ERR(a_command, "Credentials already exist");
    }
}

void
data::Database::removeCredentialsNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(argCount(1).noVars());
    auto num = CMD_GET_ARG_AS_NUM(0, m_conn_storage.size());
    m_conn_storage.erase(m_conn_storage.begin() + num);
    PRINT_CMD_MSG(a_command, "Deleted %lu credential", num + 1);
}

//-----------------------------------------------------------------------------
// Print databse information
//-----------------------------------------------------------------------------

void
data::Database::showCredentialsNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(noArgs().noVars());

    auto info = core::TablePrinter::print(
        m_conn_storage, {"id", "name", "surname", "weight", "high",
                         "building_numder", "x", "y", "street_name"});

    PRINT_CMD_MSG(a_command, "Database connection info:\n%Ы", info);
}

//-----------------------------------------------------------------------------
// Obtained connection management
//-----------------------------------------------------------------------------

void
data::Database::obtainConnectionNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(argCount(1).noVars());
    auto num = a_command.getArgumentAsNumber(0);
    m_obtained_connection.create(m_conn_storage[num].obj.get(), num);
    PRINT_CMD_MSG(a_command,
                  "Successfully obtain connection from pool number %d",
                  num + 1);
}

void
data::Database::returnConnectionNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(noArgs().noVars());
    auto pool_id = m_obtained_connection.obj.getPollId();
    m_obtained_connection.destroy();
    PRINT_CMD_MSG(a_command,
                  "Successfully release connection from pool number %d",
                  pool_id + 1);
}

void
data::Database::currentConnectionNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(noArgs().noVars());

    if (!m_obtained_connection.hasValue())
    {
        PRINT_CMD_ERR(a_command, "No connection obtained at the moment");
        return;
    }

    auto pool_id = m_obtained_connection.obj.getPollId();
    auto cred    = core::TablePrinter::printRow(m_conn_storage[pool_id], {""});
    PRINT_CMD_MSG(a_command, "Currently obtained connetion credentials:\n%s",
                  cred);
}

void
data::Database::executeConnectionNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(argCount(1).noVars());
    auto& comm = a_command.arguments[0];
    if (comm == "recreate")
    {
        // GET_CONN_POOL_INDX(num, 1);
        // m_obtained_connection.createEnvironment(
        //     m_conn_storage[num].getCredentials());
    }
}

//-----------------------------------------------------------------------------
