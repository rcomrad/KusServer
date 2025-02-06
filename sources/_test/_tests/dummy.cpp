#include "kernel/tester/fixture.hpp"

namespace kustest
{

class UDummyTest : public Fixture
{
};

TEST_F(UDummyTest, dummy_test)
{
    EXPECT_EQ(2 + 2, 4);
}

} // namespace kustest
