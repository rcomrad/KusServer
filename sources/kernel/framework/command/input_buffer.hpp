#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <mutex>
#include <optional>

#include "kernel/utility/synchronization/condvar.hpp"

#include "command.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class InputBuffer
{
public:
    InputBuffer() noexcept;
    ~InputBuffer() noexcept;

    std::unique_ptr<char[]>&& execCommand(std::string&& a_command) noexcept;
    std::optional<Command*> obtainCommand() noexcept;

private:
    std::mutex* m_data_mutex;
    std::unique_ptr<char[]> m_result;
    Command* m_command;

    struct Context
    {
        InputBuffer* buffer;
        util::Condvar* exec_synch;
    };

    static void bufferReturn(std::unique_ptr<char[]>&& a_buffer,
                             void* a_context) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
