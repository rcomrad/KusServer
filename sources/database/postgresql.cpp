#include "postgresql.hpp"

#include <format>

#include "kernel/framework/logger/include_me.hpp"
#include "pqxx/nontransaction"

#define LOG_POSTGRES_QUERIES 1

namespace database
{

PostgreSQL::PostgreSQL(const Credentials& a_cred)
{

    auto statement = std::format(
        "user = {} password = {} host = {} port = {} dbname = {}", a_cred.user,
        a_cred.password, a_cred.hostaddr, a_cred.port, a_cred.db_name);

    LOG_INFO("Creating PostgreSQL connection with stament '%s'", statement);
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
PostgreSQL::getInt(int a_colum_number) 
{
    return m_pqxx_result_it[a_colum_number].as<int>();
}

float
PostgreSQL::getFloat(int a_colum_number) 
{
    return m_pqxx_result_it[a_colum_number].as<float>();
}

bool
PostgreSQL::getBool(int a_colum_number) 
{
    return m_pqxx_result_it[a_colum_number].as<bool>();
}

const char*
PostgreSQL::getChars(int a_colum_number) 
{
    return m_pqxx_result_it[a_colum_number].as<const char*>();
}

//--------------------------------------------------------------------------------

void
PostgreSQL::step() 
{
    m_pqxx_result_it++;
}

void
PostgreSQL::exec(const char* a_statment) 
{
#if LOG_POSTGRES_QUERIES
    LOG_INFO("Exec statement: %s", a_statment);
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
        LOG_ERROR("Exception in pqxxlib: '%s'. Request: '%s'.", e.what(),
                  a_statment);
    }
    LOG_TRACE("Exec statement finished");
}

void
PostgreSQL::closeStatement() 
{
    if (m_pqxx_statement_ptr != nullptr)
    {
        m_pqxx_statement_ptr->commit();
        m_pqxx_statement_ptr = nullptr;
    }
}

void
PostgreSQL::nontransaction(const char* a_statment) 
{
#if LOG_POSTGRES_QUERIES
    LOG_INFO("Nontransaction: %s", a_statment);
#endif

    try
    {
        pqxx::nontransaction w(*m_pqxx_connection_ptr);
        w.exec(a_statment);
        w.commit();
    }
    catch (const pqxx::sql_error& e)
    {
        // TODO: cyrilic
        LOG_ERROR("Exception in pqxxlib: '%s'. Request: '%s'.", e.what(),
                  a_statment);
    }
    LOG_TRACE("Nontransaction finished");
}

//--------------------------------------------------------------------------------

int
PostgreSQL::hasData(int num) const 
{
    return !m_pqxx_result_it[num].is_null();
}

int
PostgreSQL::getResultSize() const 
{
    return m_pqxx_result.end() - m_pqxx_result.begin();
}

//--------------------------------------------------------------------------------

}
