#pragma once

#include <thread>

#include "kernel/framework/command/input_buffer.hpp"

#include "kernel_fixture.hpp"

namespace kustest
{

class CommandsFixture : public KernelFixture
{
public:
    void terminateKernel();
    std::string execCommand(const std::string& a_command);

protected:
    CommandsFixture();
    ~CommandsFixture();

private:
    std::atomic<bool> m_is_running;
    std::thread m_exec_thread;
    core::InputBuffer m_input_buffer;

    void run() const noexcept;
};

} // namespace kustest
