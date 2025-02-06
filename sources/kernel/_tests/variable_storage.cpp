#include "kernel/framework/module/kernel.hpp"
#include "kernel/tester/kernel_fixture.hpp"

namespace kustest
{

class UTVariableKERNEL : public KernelFixture
{
};

TEST_F(UTVariableKERNEL, bool_var)
{
    auto var_num = KERNEL.addBoolVariable("var");
    EXPECT_EQ(KERNEL.getVariable(var_num), 0);
    KERNEL.setVariable(var_num, true);
    EXPECT_EQ(KERNEL.getVariable(var_num), 1);
    KERNEL.setVariable(var_num, true);
    EXPECT_EQ(KERNEL.getVariable(var_num), 1);
    KERNEL.setVariable(var_num, "false");
    EXPECT_EQ(KERNEL.getVariable(var_num), 0);
}

TEST_F(UTVariableKERNEL, range_var)
{
    auto var_num = KERNEL.addVariableInfo("var", -100, 100);
    EXPECT_EQ(KERNEL.getVariable(var_num), 0);
    KERNEL.setVariable(var_num, 45);
    EXPECT_EQ(KERNEL.getVariable(var_num), 45);
    EXPECT_THROW(KERNEL.setVariable(var_num, 145), std::runtime_error);
}

TEST_F(UTVariableKERNEL, str_var)
{
    auto var_num = KERNEL.addVariableInfo("var", {"A", "B", "C"});
    EXPECT_EQ(KERNEL.getVariable(var_num), 0);
    KERNEL.setVariable(var_num, "B");
    EXPECT_EQ(KERNEL.getVariable(var_num), 1);
    KERNEL.setVariable(var_num, "A");
    EXPECT_EQ(KERNEL.getVariable(var_num), 0);
    KERNEL.setVariable(var_num, "C");
    EXPECT_EQ(KERNEL.getVariable(var_num), 2);
    EXPECT_THROW(KERNEL.setVariable(var_num, "Z"), std::runtime_error);
}

} // namespace kustest
