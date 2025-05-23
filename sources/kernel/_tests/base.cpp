#include <iostream>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/module/register.hpp"
#include "kernel/tester/commands_fixture.hpp"

namespace kustest
{

class UTBase : public CommandsFixture
{
};

TEST_F(UTBase, basic)
{
    // EXPECT_EQ(
    //     execCommand("___internal_test"),
    //     "This command is used in unit tests. Don't use it. It's
    //     meaningless.");
}

} // namespace kustest
