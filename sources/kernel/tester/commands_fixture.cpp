#include "commands_fixture.hpp"

#include <string>
#include <string_view>

#include "kernel/framework/module/kernel.hpp"

kustest::CommandsFixture::CommandsFixture()
{
    m_exec_thread = std::thread(&CommandsFixture::run, this);
}

kustest::CommandsFixture::~CommandsFixture()
{
    KERNEL.stop();
    m_exec_thread.join();
}

std::string
kustest::CommandsFixture::execCommand(const std::string& a_command)
{
    auto ptr_result = m_input_buffer.execCommand("test_command_handler");
    std::string_view cv_result(ptr_result.get());
    auto it           = cv_result.find(':');
    auto tesxt_output = cv_result.substr(it + 2, cv_result.size());
    std::string result(tesxt_output);
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
