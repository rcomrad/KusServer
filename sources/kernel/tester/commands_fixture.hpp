#pragma once

#include <thread>

#include "kernel/framework/command/input_buffer.hpp"

#include "kernel_fixture.hpp"

namespace kustest
{

class CommandsFixture : public KernelFixture
{
protected:
    CommandsFixture();
    ~CommandsFixture();

    std::string execCommand(const std::string& a_command);

private:
    std::thread m_exec_thread;
    core::InputBuffer m_input_buffer;

    void run() const noexcept;
};

} // namespace kustest
