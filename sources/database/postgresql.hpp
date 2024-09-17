#pragma once

//--------------------------------------------------------------------------------

#include "pqxx/pqxx"
#include "utility/common/holy_trinity.hpp"
#include "utility/type/base.hpp"

#include "credentials.hpp"

//--------------------------------------------------------------------------------

namespace data
{

class PostgreSQL
{
public:
    HOLY_TRINITY_NOCOPY(PostgreSQL);
    PostgreSQL(const Credentials& a_cred);

    //----------------------------------------------------------------------------

    int getInt(int a_colum_number) noexcept;
    float getFloat(int a_colum_number) noexcept;
    bool getBool(int a_colum_number) noexcept;
    const char* getChars(int a_colum_number) noexcept;

    //----------------------------------------------------------------------------

    void step() noexcept;
    void closeStatement() noexcept;
    void exec(const char* a_statment) noexcept;
    void nontransaction(const char* a_statment) noexcept;

    word_t hasData(int num = 0) const noexcept;
    word_t getResultSize() const noexcept;

private:
    std::unique_ptr<pqxx::connection> m_pqxx_connection_ptr;
    std::unique_ptr<pqxx::work> m_pqxx_statement_ptr;
    pqxx::result m_pqxx_result;
    pqxx::result::const_iterator m_pqxx_result_it;

    //----------------------------------------------------------------------------
};
} // namespace data

//--------------------------------------------------------------------------------
