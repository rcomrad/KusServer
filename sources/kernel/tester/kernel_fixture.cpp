#include "kernel_fixture.hpp"

#include "kernel/framework/module/kernel.hpp"

kustest::KernelFixture::KernelFixture()
{
    EXPECT_NO_THROW(core::Kernel::create());
    KERNEL.setLogLevel(core::Printer::LogLevel::INFO);
    KERNEL.setOutputType(core::Printer::OutputType::FILE, "test_output.txt");
}

kustest::KernelFixture::~KernelFixture()
{
    core::Kernel::destroy();
}
