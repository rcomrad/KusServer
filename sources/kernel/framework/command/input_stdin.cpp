#include "input_stdin.hpp"

#include <iostream>

#include "kernel/framework/logger/include_me.hpp"
#include "kernel/framework/module/kernel.hpp"

core::InputSTDIN::InputSTDIN()
{

    LOG_INFO("Now listening stdin.")
    m_is_running  = true;
    m_read_thread = std::thread(&InputSTDIN::readLoop, this);
    m_read_thread.detach();
}

core::InputSTDIN::~InputSTDIN()
{
    m_is_running = false;
    m_thread_finished.wait();
    LOG_INFO("Unlistened stdin.")
}

void
core::InputSTDIN::readLoop()
{
    std::string inp;
    do
    {
        std::getline(std::cin, inp);
        auto cmd_out = m_buffer.execCommand(std::move(inp));
        printf("%s", cmd_out.get());
    } while (KERNEL.isRunning() && m_is_running);
    m_thread_finished.notify();
}
