#pragma once

#include "utility/common/holy_trinity.hpp"
#include "internal_connection.hpp"

namespace data
{

class DatabaseConnection
{
public:
    // DatabaseConnection(const DatabaseConnection&) noexcept            =
    // delete; DatabaseConnection& operator=(const DatabaseConnection&) noexcept
    // = delete; DatabaseConnection(DatabaseConnection&& other) noexcept;
    // DatabaseConnection& operator=(DatabaseConnection&& other) noexcept;
    HOLY_TRINITY_NOCOPY(DatabaseConnection);

    DatabaseConnection(InternalConnection& a_db_conn, int a_pool_id) noexcept;
    ~DatabaseConnection();

    void populateDatabse() noexcept;
    void release() noexcept;
    void createEnvironment(const data::Credentials& a_credentials) noexcept;

    size_t getPollId() const noexcept;
    bool hasValue() const noexcept;

private:
    int m_pool_id;
    InternalConnection& m_db_conn;
};

} // namespace data
