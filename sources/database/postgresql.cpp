#include "postgresql.hpp"

#include <cstring>

#include "core/logging.hpp"

#include "string/string_malloc.hpp"

#include "pqxx/nontransaction"

#include "db_credential_storage.hpp"

#define LOG_POSTGRES_QUERIES 1

data::PostgreSQL::PostgreSQL(word_t a_credentials_id)
{
    MALLOC_STR(statement, 200);
    auto cur_char_ptr = statement;

    auto& dbc = DBCredentialStorage::getCredentials(a_credentials_id);
    SPRINTF(cur_char_ptr,
            "dbname = %s user = %s password = %s hpsaddr = %s port = %s",
            dbc.name, dbc.user, dbc.password, dbc.hostaddr, dbc.port);

    //--------------------------------------------------------------------------------

    LOG_INFO("Creating PostgreSQL connection");
    try
    {
        m_pqxx_connection_ptr = std::make_unique<pqxx::connection>(statement);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Can't connect to database: ", e.what());
        static_assert("Can't connect to database");
    }

    if (m_pqxx_connection_ptr->is_open())
    {
        LOG_INFO("PostgreSQL connection ready for use");
    }
    else
    {
        LOG_ERROR("Can't_open_database");
        static_assert("Database failed");
    }
}

//--------------------------------------------------------------------------------

int
data::PostgreSQL::getInt(int a_colum_number) noexcept
{
    return m_pqxx_result_it[a_colum_number].as<int>();
}

float
data::PostgreSQL::getFloat(int a_colum_number) noexcept
{
    return m_pqxx_result_it[a_colum_number].as<float>();
}

bool
data::PostgreSQL::getBool(int a_colum_number) noexcept
{
    return m_pqxx_result_it[a_colum_number].as<bool>();
}

const char*
data::PostgreSQL::getChars(int a_colum_number) noexcept
{
    return m_pqxx_result_it[a_colum_number].as<const char*>();
}

//--------------------------------------------------------------------------------

void
data::PostgreSQL::step() noexcept
{
    m_pqxx_result_it++;
}

void
data::PostgreSQL::exec(const char* a_statment) noexcept
{
#if LOG_POSTGRES_QUERIES
    LOG_INFO(a_statment);
#endif

    closeStatement();
    try
    {
        // TODO: check
        m_pqxx_statement_ptr =
            std::make_unique<pqxx::work>(*m_pqxx_connection_ptr);
        m_pqxx_result    = pqxx::result(m_pqxx_statement_ptr->exec(a_statment));
        m_pqxx_result_it = --m_pqxx_result.begin();
    }
    catch (const pqxx::sql_error& e)
    {
        // TODO: cyrilic
        LOG_ERROR(e.what(), "req:", a_statment);
    }
}

void
data::PostgreSQL::closeStatement() noexcept
{
    if (m_pqxx_statement_ptr != nullptr)
    {
        m_pqxx_statement_ptr->commit();
        m_pqxx_statement_ptr = nullptr;
    }
}

void
data::PostgreSQL::nontransaction(const char* a_statment) noexcept
{
#if LOG_POSTGRES_QUERIES
    LOG_INFO(a_statment);
#endif

    try
    {
        pqxx::nontransaction w(*m_pqxx_connection_ptr);
        w.exec(a_statment);
        w.commit();
    }
    catch (const pqxx::sql_error& e)
    {
        std::string s(e.what());
        LOG_ERROR(s, "req:", a_statment);
    }
}

//--------------------------------------------------------------------------------

word_t
data::PostgreSQL::hasData(int num) const noexcept
{
    return !m_pqxx_result_it[num].is_null();
}

word_t
data::PostgreSQL::getResultSize() const noexcept
{
    return m_pqxx_result.end() - m_pqxx_result.begin();
}

//--------------------------------------------------------------------------------
