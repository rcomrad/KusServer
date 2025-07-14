#include "commands_fixture.hpp"

#include <string>
#include <string_view>

#include "kernel/framework/core/kernel.hpp"

kustest::CommandsFixture::CommandsFixture() : m_is_running(false)
{
    m_exec_thread = std::thread(&CommandsFixture::run, this);
    m_is_running  = true;
}

kustest::CommandsFixture::~CommandsFixture()
{
    terminateKernel();
}

std::string
kustest::CommandsFixture::execCommand(const std::string& a_command)
{
    auto ptr_result = m_input_buffer.execCommand(a_command.data());
    std::string result(ptr_result.get());
    while (result.size() && std::isspace(result.back()))
    {
        result.pop_back();
    }
    return result;
}

void
kustest::CommandsFixture::run() const noexcept
{
    EXPECT_NO_THROW(KERNEL.run());
}

void
kustest::CommandsFixture::terminateKernel()
{
    if (m_is_running)
    {
        KERNEL.stop();
        m_is_running = false;
        m_exec_thread.join();
    }
}
