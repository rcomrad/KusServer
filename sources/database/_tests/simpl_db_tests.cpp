#include <barrier>

#include "kernel/framework/core/kernel.hpp"

#include "admin_user_fixture.hpp"

namespace database
{

class SimpleDBTests : public AdminUserFixture
{
};

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

TEST_F(SimpleDBTests, Smoke)
{
    auto& conn = m_pool->get();

    conn.createTable<TestTable>();

    populateTT(conn);
    checkTT(conn);

    conn.deleteTable<TestTable>();
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

TEST_F(SimpleDBTests, MassActions)
{
    auto& conn = m_pool->get();
    m_exec->createAll(conn);

    populateTT(conn);
    populateST(conn);
    checkTT(conn);
    checkST(conn);

    m_exec->deleteAll(conn);
    EXPECT_FALSE(conn.select<TestTable>("id = 1").has_value());
    EXPECT_FALSE(conn.select<SecondTable>("id = 1").has_value());

    m_exec->createAll(conn);
    EXPECT_FALSE(conn.select<TestTable>("id = 1").has_value());
    EXPECT_FALSE(conn.select<SecondTable>("id = 1").has_value());

    populateTT(conn);
    populateST(conn);
    checkTT(conn);
    checkST(conn);
}

TEST_F(SimpleDBTests, Dump)
{
    auto& conn = m_pool->get();
    m_exec->createAll(conn);

    populateTT(conn);
    populateST(conn);
    checkTT(conn);
    checkST(conn);

    std::string tt_data = "TestTable@\n"
                          "1;10;aba;\n"
                          "2;17;vbb;\n"
                          "~\n";
    std::string ts_data = "SecondTable@\n"
                          "1;str1;-5;0;\n"
                          "2;str1;0;0;\n"
                          "~\n";
    EXPECT_EQ(conn.dump<TestTable>(), tt_data);
    EXPECT_EQ(conn.dump<SecondTable>(), ts_data);
    EXPECT_EQ(m_exec->dumpAll(conn), ts_data + tt_data);
}

TEST_F(SimpleDBTests, Load)
{
    auto& conn = m_pool->get();
    m_exec->createAll(conn);

    std::vector<std::string> data = {
        "TestTable@",  "1;10;aba;",    "2;17;vbb;",   "~", "SecondTable@",
        "#1;isa;0;7;", "1;str1;-5;0;", "2;str1;0;0;", "~"};
    m_exec->load(conn, data);

    checkTT(conn);
    checkST(conn);
}

TEST_F(SimpleDBTests, Update)
{
    auto& conn = m_pool->get();
    m_exec->createAll(conn);

    populateTT(conn);
    populateST(conn);
    checkTT(conn);
    checkST(conn);

    auto temp    = conn.select<TestTable>("id = 1").value();
    auto old_str = temp.str_1;
    temp.str_1   = "updated_str";
    conn.update(temp);

    auto arr = std::vector<TestTable>{getSecondTT(), temp};
    EXPECT_EQ(conn.selectArray<TestTable>(), arr);
    checkST(conn);

    temp.str_1 = old_str;
    conn.update(temp);
    arr = std::vector<TestTable>{getSecondTT(), temp};
    EXPECT_EQ(conn.selectArray<TestTable>(), arr);
    checkST(conn);
}

TEST_F(SimpleDBTests, Drop)
{
    auto& conn = m_pool->get();
    m_exec->createAll(conn);

    populateTT(conn);
    populateST(conn);
    checkTT(conn);
    checkST(conn);

    auto temp = conn.select<TestTable>("id = 1").value();
    conn.drop(temp);

    auto arr = std::vector<TestTable>{getSecondTT()};
    EXPECT_EQ(conn.selectArray<TestTable>(), arr);
    checkST(conn);

    temp.id = 0;
    conn.insert(temp);
    temp.id = 3;
    arr     = std::vector<TestTable>{getSecondTT(), temp};
    EXPECT_EQ(conn.selectArray<TestTable>(), arr);
    checkST(conn);
}

CREATE_STRUCT(TestCounter, ((int, num)));
TEST_F(SimpleDBTests, MultipleAcsess)
{
    {
        auto& conn = m_pool->get();
        m_exec->createAll(conn);

        TestCounter init_data;
        init_data.num = 0;
        conn.insert(init_data);
    }

    const int thread_count    = 15;
    const int increment_count = 10000;

    std::barrier bar(thread_count);
    auto lumbda = [&]()
    {
        bar.arrive_and_wait();
        for (int i = 0; i < increment_count; ++i)
        {
            auto& conn = m_pool->get();
            auto data  = conn.select<TestCounter>("id = 1").value();
            data.num++;
            conn.update(data);
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(lumbda);
    }

    for (auto& i : threads) i.join();

    {
        auto& conn = m_pool->get();
        auto data  = conn.select<TestCounter>("id = 1").value();
        EXPECT_EQ(data.num, thread_count * increment_count);
    }
}

//--------------------------------------------------------------------------------

} // namespace database
