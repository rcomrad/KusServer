#include "input_stdin.hpp"

#include <iostream>

#include "core/module/registry.hpp"

#include "registry.hpp"

SINGLETON_DEFINITOR(core, InputSTDIN);

core::InputSTDIN::InputSTDIN() noexcept
{
    m_read_thread = std::thread(&InputSTDIN::readLoop, this);
    m_read_thread.detach();
}

void
core::InputSTDIN::listenNonstatic() noexcept
{
    CommandHandler::listen(&m_buffer);
}

void
core::InputSTDIN::unlistenNonstatic() noexcept
{
    CommandHandler::unlisten(&m_buffer);
}

void
core::InputSTDIN::readLoop() noexcept
{
    std::string inp;
    while (ModuleRegistry::isRunning())
    {
        std::getline(std::cin, inp);
        auto cmd_out = m_buffer.execCommand(std::move(inp));
        printf("%s", cmd_out.get());
    }
}
