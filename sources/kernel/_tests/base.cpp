#include <iostream>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/tester/commands_fixture.hpp"

namespace kustest
{

class UTBase : public CommandsFixture
{
};

TEST_F(UTBase, basic)
{
    EXPECT_EQ(execCommand("___internal_test"), "Test successful!");
}

} // namespace kustest
