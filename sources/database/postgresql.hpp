#pragma once

//--------------------------------------------------------------------------------

#include "kernel/utility/macroses/holy_trinity.hpp"
#include "pqxx/pqxx"

#include "credentials.hpp"

#include "kernel/utility/type/concepts.hpp"

//--------------------------------------------------------------------------------

namespace database
{

class PostgreSQL
{
public:
    HOLY_TRINITY_NOCOPY(PostgreSQL);

    PostgreSQL(const Credentials& a_cred);

    //----------------------------------------------------------------------------

    int getInt(int a_colum_number);
    float getFloat(int a_colum_number);
    bool getBool(int a_colum_number);
    const char* getChars(int a_colum_number);

    template <util::IsNotStdString T>
    T get(int a_colum_number)
    {
        return m_pqxx_result_it[a_colum_number].as<T>();
    }

    template <util::IsStdString T>
    T get(int a_colum_number)
    {
        // TODO: free?
        const char* res = m_pqxx_result_it[a_colum_number].as<const char*>();
        return std::string(res);
    }

    // template <typename T>
    // T get(int a_colum_number)
    // {
    //     T t;
    //     return t;
    // }

    //----------------------------------------------------------------------------

    void step();
    void closeStatement();
    void exec(const char* a_statment);
    void nontransaction(const char* a_statment);

    int hasData(int num = 0) const;
    int getResultSize() const;

private:
    std::unique_ptr<pqxx::connection> m_pqxx_connection_ptr;
    std::unique_ptr<pqxx::work> m_pqxx_statement_ptr;
    pqxx::result m_pqxx_result;
    pqxx::result::const_iterator m_pqxx_result_it;

    //----------------------------------------------------------------------------
};
} // namespace database

//--------------------------------------------------------------------------------
