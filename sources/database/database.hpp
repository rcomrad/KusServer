#pragma once

//--------------------------------------------------------------------------------

#include "core/holy_trinity.hpp"
#include "core/module.hpp"

#include "database_connection.hpp"

//--------------------------------------------------------------------------------

namespace data
{

class Database : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Database);

    void initialize() noexcept override;

    SINGL_RET_METHOD(DatabaseConnection&, get, (word_t a_user_id));
    SINGL_VOID_METHOD(put, (DatabaseConnection & a_conn))

private:
    std::vector<DatabaseConnection> m_db_connections;

    Database() noexcept;
};

} // namespace data
