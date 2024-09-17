#pragma once

#include <cstring>

#include "utility/type/base.hpp"

#include "credentials.hpp"
#include "postgresql.hpp"
#include "struct_data.hpp"

namespace data
{

class SQLConnection
{
public:
    HOLY_TRINITY_NOCOPY(SQLConnection);
    SQLConnection(const Credentials& a_credentials) noexcept;

    word_t insert(void* a_result_ptr, struct_id_t a_struct_id) noexcept;
    void select(void* a_result_ptr,
                struct_id_t a_struct_id,
                const char* a_condition = nullptr) noexcept;

    void createEnvironment(const Credentials& a_credentials) noexcept;

    void createTable(const char* a_owner_name,
                     const char* a_table_name,
                     const char* a_table_body) noexcept;

private:
    PostgreSQL m_db_conn;

    void execAndReset(char* a_statement_ptr, char* a_cur_char_ptr) noexcept;

    static inline auto getInsertStatementSize(
        const data::StructData& a_struct_data) noexcept
    {
        return 30 + 1 * a_struct_data.count + DatabaseStructNameMaxSize +
               a_struct_data.str_max_size;
    }

    static inline auto getSelectStatementSize(
        const data::StructData& a_struct_data,
        const char* a_condition) noexcept
    {
        return 20 + DatabaseStructNameMaxSize +
               std::max(a_struct_data.column_names_size, (uint16_t)3) +
               strlen(a_condition);
    }
};

} // namespace data
