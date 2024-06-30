#include "database_connection.hpp"

#include "string/string_malloc.hpp"

#include "struct_storage.hpp"

data::DatabaseConnection::DatabaseConnection(word_t a_credentials_id,
                                             word_t a_connection_id) noexcept
    : m_sql_conn(a_credentials_id), m_connection_id(a_connection_id)
{
}

void
data::DatabaseConnection::populateDatabse() noexcept
{
    MALLOC_STR(table_body, 200);
    auto body_ptr = table_body;
    for (size_t i = 0; i < StructStorage::getSize(); ++i)
    {
        auto struct_data = StructStorage::getStructData(i);
        for (word_t i = 0; i < struct_data.count; ++i)
        {
            auto& var_ref = struct_data.vars[i];
            SPRINTF(body_ptr, "%s", struct_data.name);
            switch (var_ref.type)
            {
                case CPPTypeEnum::INT:
                    SPRINTF(body_ptr, " int,");
                    break;
                case CPPTypeEnum::DOUBLE:
                    SPRINTF(body_ptr, " real,");
                    break;
                case CPPTypeEnum::BOOL:
                    SPRINTF(body_ptr, " boolean,");
                    break;
                case CPPTypeEnum::CHAR_PTR:
                    SPRINTF(body_ptr, "  character varying(%lu),",
                            var_ref.size);
                    break;
            }
        }
        *(--body_ptr) = '\0';
        m_sql_conn.createTable("rcomrad", struct_data.name, table_body);
    }
}
