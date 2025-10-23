#pragma once

#include "database_fixture.hpp"

namespace database
{

class AdminUserFixture : public DatabaseFixture
{
protected:
    void SetUp() final;
    void TearDown() final;

    database::ConnectionPool* m_pool;
    database::MassExecutor* m_exec;
};

} // namespace database
