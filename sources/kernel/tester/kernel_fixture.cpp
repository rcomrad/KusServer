#include "kernel_fixture.hpp"

#include "kernel/framework/module/kernel.hpp"

kustest::KernelFixture::KernelFixture()
{
    EXPECT_NO_THROW(core::Kernel::create());
}

kustest::KernelFixture::~KernelFixture()
{
    core::Kernel::destroy();
}
