#include "database/db_module.hpp"

#include "kernel/tester/commands_fixture.hpp"

namespace database
{

class __DatabaseFixtureCreator : public kustest::CommandsFixture
{
protected:
    __DatabaseFixtureCreator();
    ~__DatabaseFixtureCreator() = default;
};

class DatabaseFixture : public __DatabaseFixtureCreator
{
protected:
    DatabaseFixture();
    ~DatabaseFixture() = default;

    DBModule& m_database;
};

} // namespace database
