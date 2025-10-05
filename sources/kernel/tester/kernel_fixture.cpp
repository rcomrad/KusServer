#include "kernel_fixture.hpp"

#include "kernel/framework/core/kernel.hpp"

kustest::KernelFixture::KernelFixture()
{
    EXPECT_NO_THROW(core::Kernel::create());
}

kustest::KernelFixture::~KernelFixture()
{
    core::Kernel::destroy();
}
