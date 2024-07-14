#include "database.hpp"

#include <cstring>

#include "file_system/file_read.hpp"
#include "file_system/file_write.hpp"
#include "file_system/path.hpp"
#include "file_system/read_target.hpp"

// GRANT CREATE DATABASE TO maxroach;

//-----------------------------------------------------------------------------

#define CREDENTIALS_FOLDER "bin"
#define CREDENTIALS_FILE   "db_credentials.txt"

#define EXPAND_CREDANTIALS(var_name)                                      \
    var_name.fields.name, var_name.fields.user, var_name.fields.password, \
        var_name.fields.hostaddr, var_name.fields.port, var_name.fields.shame

//-----------------------------------------------------------------------------

SINGLETON_DEFINITOR(data, Database);

data::Database::Database() noexcept
    : Module("credential_storage"), m_obtained_connection(nullptr, 0)
{
}

void
data::Database::initialize() noexcept
{
    auto path = fs::Path::getFilePath(CREDENTIALS_FOLDER, CREDENTIALS_FILE);
    if (path.has_value())
    {
        auto credential =
            fs::FileRead::getWords(fs::ReadFromFilePath(path.value()));

        for (auto& i : credential)
        {
            auto conn = ConnectionPool::create(i);
            if (conn.has_value())
            {
                m_conn_storage.emplace_back(std::move(conn.value()));
            }
        }
    }
}

data::DatabaseConnection
data::Database::getConnectionNonstatic(size_t a_pool_id) noexcept
{
    return m_conn_storage[a_pool_id].get(a_pool_id);
}

void
data::Database::putConnectionNonstatic(SQLConnection* a_sql_conn,
                                       size_t a_pool_id) noexcept
{
    m_conn_storage[a_pool_id].put(a_sql_conn);
}

void
data::Database::commandSetup() noexcept
{
    registerCommand("data_add", addCredentials);
    registerCommand("data_add_base", addBaseCredentials);
    registerCommand("data_remove", removeCredentials);
    registerCommand("data_show", showCredentials);

    registerCommand("data_obtain", obtainConnection);
    registerCommand("data_return", returnConnection);
    registerCommand("data_cur", currentConnection);
}

//-----------------------------------------------------------------------------
// Add/Remove commands
//-----------------------------------------------------------------------------

void
data::Database::addCredentialsNonstatic(core::Command& aCommand) noexcept
{
    ARGUMENT_SIZE_CHECK(6);

    auto conn = ConnectionPool::create(aCommand.arguments);
    if (conn.has_value())
    {

        m_conn_storage.emplace_back(std::move(conn.value()));
        dumpCredentialsToFIle();
        COMMAND_RETURN_MSG(aCommand, "Credentials successfully added");
    }
    else
    {
        COMMAND_RETURN_ERROR(aCommand, "Credentials already exist");
    }
}

void
data::Database::addBaseCredentialsNonstatic(core::Command& aCommand) noexcept
{
    ARGUMENT_SIZE_CHECK(1);
    Credentials::setDefault(aCommand.arguments);
    addCredentialsNonstatic(aCommand);
}

void
data::Database::removeCredentialsNonstatic(core::Command& aCommand) noexcept
{
    ARGUMENT_SIZE_CHECK(1);
    GET_ARG_AS_NUM(num, 0);

    if (m_conn_storage.size() >= num)
    {
        m_conn_storage.erase(m_conn_storage.begin() + num - 1);
        dumpCredentialsToFIle();
        COMMAND_RETURN_MSG(aCommand, "Deleted %lu credential", num);
    }
    else
    {
        COMMAND_RETURN_ERROR(
            aCommand,
            "Wrong credential number. Expected no more than %lu, got %lu",
            m_conn_storage.size(), num);
    }
}

//-----------------------------------------------------------------------------
// Print databse information
//-----------------------------------------------------------------------------

void
data::Database::showCredentialsNonstatic(core::Command& aCommand) noexcept
{
    static auto table = configurateShowTable();

    const char command_head[]        = "Database credentials:\n";
    constexpr auto command_head_size = std::size(command_head);

    aCommand.setResultBufferSize(table.getSize() *
                                     (m_conn_storage.size() * 2 + 3) +
                                 command_head_size + 10);
    char* cur_ptr = aCommand.getResultBuffer();

    cur_ptr += sprintf(cur_ptr, command_head);
    table.printHead(&cur_ptr);

    for (int i = 0; i < m_conn_storage.size(); ++i)
    {
        table.printData(&cur_ptr, i + 1);
        m_conn_storage[i].printData(&cur_ptr, table, true);
    }
}

core::TablePrintHelper
data::Database::configurateShowTable() noexcept
{
    core::TablePrintHelper a_table; // For define
    PUSH_COMBINED_COLUMN(Database, m_conn_storage.size(), 3, "#");
    ConnectionPool::configurateTable(a_table, true);
    return a_table;
}

//-----------------------------------------------------------------------------

void
data::Database::obtainConnectionNonstatic(core::Command& aCommand) noexcept
{
    ARGUMENT_SIZE_CHECK(1);
    GET_ARG_AS_NUM(num, 0);
    num -= 1;

    if (m_conn_storage.size() > num)
    {
        m_obtained_connection = std::move(m_conn_storage[num].get(num));
        COMMAND_RETURN_MSG(aCommand,
                           "Successfully obtain connection from pool number %d",
                           num + 1);
    }
    else
    {
        COMMAND_RETURN_ERROR(
            aCommand,
            "Wrong credential number. Expected no more than %lu, got %lu",
            m_conn_storage.size(), num);
    }
}

void
data::Database::returnConnectionNonstatic(core::Command& aCommand) noexcept
{
    ARGUMENT_SIZE_CHECK(0);
    auto pool_id = m_obtained_connection.getPollId();
    m_obtained_connection.release();
    COMMAND_RETURN_MSG(aCommand,
                       "Successfully release connection from pool number %d",
                       pool_id + 1);
}

void
data::Database::currentConnectionNonstatic(core::Command& aCommand) noexcept
{
    ARGUMENT_SIZE_CHECK(0);
    static auto table = configurateCurTable();

    const char command_head[]  = "Currently obtained connetion credentials:\n";
    const char no_connection[] = "No connection obtained at the moment";
    constexpr auto command_head_size =
        std::max(std::size(command_head), std::size(no_connection));

    aCommand.setResultBufferSize(table.getSize() * 5 + command_head_size + 10);
    char* cur_ptr = aCommand.getResultBuffer();

    if (!m_obtained_connection.hasValue())
    {
        COMMAND_RETURN_ERROR(aCommand, "No connection obtained at the moment");
        return;
    }

    cur_ptr += sprintf(cur_ptr, command_head);
    table.printHead(&cur_ptr);

    auto pool_id = m_obtained_connection.getPollId();
    m_conn_storage[pool_id].printData(&cur_ptr, table, false);
}

core::TablePrintHelper
data::Database::configurateCurTable() noexcept
{
    core::TablePrintHelper a_table; // For define
    ConnectionPool::configurateTable(a_table, false);
    return a_table;
}

//-----------------------------------------------------------------------------

void
data::Database::dumpCredentialsToFIle() const noexcept
{
    fs::FileWrite file(CREDENTIALS_FOLDER, CREDENTIALS_FILE);
    for (const auto& i : m_conn_storage)
    {
        i.dumpCredentialsToFIle(file);
    }
}
