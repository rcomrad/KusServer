#include "database_fixture.hpp"

#include "kernel/framework/core/kernel.hpp"

namespace database
{

__DatabaseFixtureCreator::__DatabaseFixtureCreator()
{
    execCommand("mod_add database");
}

DatabaseFixture::DatabaseFixture()
    : m_database(KERNEL.getModuleRef<DBModule>("database"))
{
}

} // namespace database
