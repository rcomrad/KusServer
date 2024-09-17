#include "database_connection.hpp"

#include <string>
#include <unordered_map>

#include "string/string_malloc.hpp"

#include "database.hpp"

#include "struct_storage.hpp"

enum
{
    NULL_POLL_ID = -1
};

data::DatabaseConnection::DatabaseConnection(InternalConnection& a_db_conn,
                                             int a_pool_id) noexcept
    : m_db_conn(a_db_conn), m_pool_id(a_pool_id)
{
}

data::DatabaseConnection::~DatabaseConnection()
{
    release();
}

// data::DatabaseConnection::DatabaseConnection(
//     DatabaseConnection&& other) noexcept
// {
//     *this = std::move(other);
// }

// data::DatabaseConnection&
// data::DatabaseConnection::operator=(DatabaseConnection&& other) noexcept
// {
//     release();

//     m_pool_id = other.m_pool_id;

//     m_sql_conn       = other.m_sql_conn;
//     other.m_sql_conn = nullptr;

//     return *this;
// }

void
data::DatabaseConnection::release() noexcept
{
    if (m_pool_id != NULL_POLL_ID)
    {
        Database::putConnection(m_pool_id, m_db_conn);
        m_pool_id = NULL_POLL_ID;
    }
}

size_t
data::DatabaseConnection::getPollId() const noexcept
{
    return m_pool_id;
}

bool
data::DatabaseConnection::hasValue() const noexcept
{
    return m_pool_id != NULL_POLL_ID;
}

void
data::DatabaseConnection::populateDatabse() noexcept
{
    // MALLOC_STR(table_body, 200);
    // auto body_ptr = table_body;
    // for (size_t i = 0; i < StructStorage::getSize(); ++i)
    // {
    //     auto struct_data = StructStorage::getStructData(i);
    //     for (word_t i = 0; i < struct_data.count; ++i)
    //     {
    //         auto& var_ref = struct_data.vars[i];
    //         SPRINTF(body_ptr, "%s", struct_data.name);
    //         switch (var_ref.type)
    //         {
    //             case CPPTypeEnum::INT:
    //                 SPRINTF(body_ptr, " int,");
    //                 break;
    //             case CPPTypeEnum::DOUBLE:
    //                 SPRINTF(body_ptr, " real,");
    //                 break;
    //             case CPPTypeEnum::BOOL:
    //                 SPRINTF(body_ptr, " boolean,");
    //                 break;
    //             case CPPTypeEnum::CHAR_PTR:
    //                 SPRINTF(body_ptr, "  character varying(%lu),",
    //                         var_ref.size);
    //                 break;
    //         }
    //     }
    //     *(--body_ptr) = '\0';
    //     m_sql_conn->createTable("rcomrad", struct_data.name, table_body);
    // }
}

void
data::DatabaseConnection::createEnvironment(
    const data::Credentials& a_credentials) noexcept
{
    // m_sql_conn->createEnvironment(a_credentials);
}
