#include "kernel/tester/fixture.hpp"

namespace kustest
{

class ArithmeticTest : public Fixture
{
};

//--------------------------------------------------------------------------------

int
foo(unsigned n, int m)
{
    return n / m;
}

TEST_F(ArithmeticTest, division)
{
    EXPECT_EQ(foo(1, -1), 0);
}

//--------------------------------------------------------------------------------

} // namespace kustest
