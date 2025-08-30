#include "database/table_specific.hpp"
#include "database_fixture.hpp"

#include "kernel/framework/core/kernel.hpp"

namespace database
{

//--------------------------------------------------------------------------------

struct TestTable
{
    int id;
    int num;
    std::string str_1;
};

template <>
class TableSpecific<TestTable>
{
public:
    std::string_view getTableName()
    {
        return "test_table";
    }

    void insert(util::StringBuilder& a_sb, const TestTable& a_data)
    {
        {
            auto scoped = a_sb.addSeparator(',');
            a_sb.add("default");
            a_sb.add(a_data.num);
        }
        a_sb.addQuotated(a_data.str_1);
    }

    void select(PostgreSQL& a_psql, TestTable& a_data)
    {
        a_data.id    = a_psql.getInt(0);
        a_data.num   = a_psql.getInt(1);
        a_data.str_1 = std::string(a_psql.getChars(2));
    }
};

TEST_F(DatabaseFixture, smoke)
{
    execCommand("db_add_cred postgres admin 127.0.0.1 5437 postgres");

    auto& adm_pool = m_database.getConnectionPool("postgres");
    auto& adm_conn = adm_pool.get();

    adm_conn.createTable("test_table",
                         "num INTEGER NOT NULL, str_1 VARCHAR(50) NOT NULL");

    TestTable data;
    data.num   = 10;
    data.str_1 = "aba";
    adm_conn.insert(data);

    data.num   = 17;
    data.str_1 = "vbb";
    adm_conn.insert(data);

    data = adm_conn.select<TestTable>("id = 1");
    EXPECT_EQ(data.num, 10);
    EXPECT_EQ(data.str_1, "aba");

    data = adm_conn.select<TestTable>("id = 2");
    EXPECT_EQ(data.num, 17);
    EXPECT_EQ(data.str_1, "vbb");

    adm_conn.deleteTable("test_table");
}

//--------------------------------------------------------------------------------

} // namespace database
