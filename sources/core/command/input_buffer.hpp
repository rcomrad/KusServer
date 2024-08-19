#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <mutex>
#include <optional>

#include "utility/synchronization/condvar.hpp"

#include "command_extend.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class InputBuffer
{
public:
    InputBuffer() noexcept;
    ~InputBuffer() noexcept;

    std::unique_ptr<char[]>&& execCommand(std::string&& a_command) noexcept;
    std::optional<CommandExtend*> obtainCommand() noexcept;

private:
    std::mutex m_data_mutex;
    std::unique_ptr<char[]> m_result;
    CommandExtend* m_command;

    struct Context
    {
        InputBuffer* buffer;
        Condvar* exec_synch;
    };

    static void bufferReturn(std::unique_ptr<char[]>&& a_buffer,
                             void* a_context) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
