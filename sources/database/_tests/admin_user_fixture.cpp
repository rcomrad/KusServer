#include "admin_user_fixture.hpp"

namespace database
{

void
AdminUserFixture::SetUp()
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");
    m_pool     = &m_database.getConnectionPool("postgres");
    m_exec     = &database::MassExecutor::getInstance();
    auto& conn = m_pool->get();
    m_exec->deleteAll(conn);
}

void
AdminUserFixture::TearDown()
{
    auto& conn = m_pool->get();
    m_exec->deleteAll(conn);
}

} // namespace database
