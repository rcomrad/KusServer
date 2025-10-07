#include "database_fixture.hpp"

#include "kernel/framework/core/kernel.hpp"

namespace database
{

//--------------------------------------------------------------------------------

CREATE_STRUCT(TestTable, ((int, num))((std::string, str_1)))

TestTable
getFirstTT(int id = 1)
{
    return TestTable(id, 10, "aba");
}
TestTable
getSecondTT(int id = 2)
{
    return TestTable(id, 17, "vbb");
}

void
populateTT(SQLConnection& a_conn)
{
    // id = 0 is new element
    EXPECT_EQ(a_conn.insert(getFirstTT(0)), 1);
    EXPECT_EQ(a_conn.insert(getSecondTT(0)), 2);
}

void
checkTT(SQLConnection& a_conn)
{
    EXPECT_EQ(a_conn.selectUnsafe<TestTable>("id = 1"), getFirstTT());
    EXPECT_EQ(a_conn.selectUnsafe<TestTable>("id = 2"), getSecondTT());

    auto arr = std::vector<TestTable>{getFirstTT(), getSecondTT()};
    EXPECT_EQ(a_conn.selectArray<TestTable>(), arr);
}

TEST_F(DatabaseFixture, Smoke)
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");
    auto& adm_pool = m_database.getConnectionPool("postgres");
    auto& adm_conn = adm_pool.get();

    ///

    adm_conn.createTable<TestTable>();

    populateTT(adm_conn);
    checkTT(adm_conn);

    adm_conn.deleteTable<TestTable>();
}

CREATE_STRUCT(SecondTable, ((std::string, wuf))((int, a))((int, b)))

SecondTable
getFirstST(int id = 1)
{
    return SecondTable(id, "str1", -5, 0);
}
SecondTable
getSecondST(int id = 2)
{
    return SecondTable(id, "str1", 0, 0);
}

void
populateST(SQLConnection& a_conn)
{
    // id = 0 is new element
    EXPECT_EQ(a_conn.insert(getFirstST(0)), 1);
    EXPECT_EQ(a_conn.insert(getSecondST(0)), 2);
}

void
checkST(SQLConnection& a_conn)
{
    EXPECT_EQ(a_conn.selectUnsafe<SecondTable>("id = 1"), getFirstST());
    EXPECT_EQ(a_conn.selectUnsafe<SecondTable>("id = 2"), getSecondST());
}

TEST_F(DatabaseFixture, MassActions)
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");
    auto& adm_pool = m_database.getConnectionPool("postgres");
    auto& adm_conn = adm_pool.get();

    auto& exec = database::MassExecutor::getInstance();

    ///

    exec.deleteAll(adm_conn);
    exec.createAll(adm_conn);

    populateTT(adm_conn);
    populateST(adm_conn);
    checkTT(adm_conn);
    checkST(adm_conn);

    exec.deleteAll(adm_conn);
    EXPECT_FALSE(adm_conn.select<TestTable>("id = 1").has_value());
    EXPECT_FALSE(adm_conn.select<SecondTable>("id = 1").has_value());

    exec.createAll(adm_conn);
    EXPECT_FALSE(adm_conn.select<TestTable>("id = 1").has_value());
    EXPECT_FALSE(adm_conn.select<SecondTable>("id = 1").has_value());

    populateTT(adm_conn);
    populateST(adm_conn);
    checkTT(adm_conn);
    checkST(adm_conn);

    exec.deleteAll(adm_conn);
}

TEST_F(DatabaseFixture, Dump)
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");
    auto& adm_pool = m_database.getConnectionPool("postgres");
    auto& adm_conn = adm_pool.get();

    auto& exec = database::MassExecutor::getInstance();

    ///

    exec.deleteAll(adm_conn);
    exec.createAll(adm_conn);

    populateTT(adm_conn);
    populateST(adm_conn);
    checkTT(adm_conn);
    checkST(adm_conn);

    std::string tt_data = "TestTable@\n"
                          "1;10;aba;\n"
                          "2;17;vbb;\n"
                          "~\n";
    std::string ts_data = "SecondTable@\n"
                          "1;str1;-5;0;\n"
                          "2;str1;0;0;\n"
                          "~\n";
    EXPECT_EQ(adm_conn.dump<TestTable>(), tt_data);
    EXPECT_EQ(adm_conn.dump<SecondTable>(), ts_data);
    EXPECT_EQ(exec.dumpAll(adm_conn), ts_data + tt_data);

    exec.deleteAll(adm_conn);
}

TEST_F(DatabaseFixture, Load)
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");
    auto& adm_pool = m_database.getConnectionPool("postgres");
    auto& adm_conn = adm_pool.get();

    auto& exec = database::MassExecutor::getInstance();

    ///

    exec.deleteAll(adm_conn);
    exec.createAll(adm_conn);

    std::vector<std::string> data = {
        "TestTable@",   "1;10;aba;",    "2;17;vbb;",   "~",
        "SecondTable@", "#1;isa;0;7;","1;str1;-5;0;", "2;str1;0;0;", "~"};
    exec.load(adm_conn, data);

    checkTT(adm_conn);
    checkST(adm_conn);

    exec.deleteAll(adm_conn);
}

TEST_F(DatabaseFixture, up)
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");
    auto& adm_pool = m_database.getConnectionPool("postgres");
    auto& adm_conn = adm_pool.get();

    auto& exec = database::MassExecutor::getInstance();

    ///

    exec.deleteAll(adm_conn);
    exec.createAll(adm_conn);

    std::vector<std::string> data = {
        "TestTable@",   "1;10;aba;",    "2;17;vbb;",   "~",
        "SecondTable@", "#1;isa;0;7;","1;str1;-5;0;", "2;str1;0;0;", "~"};
    exec.load(adm_conn, data);

    checkTT(adm_conn);
    checkST(adm_conn);

    exec.deleteAll(adm_conn);
}

//--------------------------------------------------------------------------------

} // namespace database
