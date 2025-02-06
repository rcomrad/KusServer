#include "input_buffer.hpp"

#include "kernel/framework/module/kernel.hpp"

core::InputBuffer::InputBuffer() noexcept : m_command(nullptr)
{
    m_data_mutex = &KERNEL.listenCommandBuffer(this);
}

core::InputBuffer::~InputBuffer() noexcept
{
    const std::lock_guard<std::mutex> lock(*m_data_mutex);
    KERNEL.unlistenCommandBuffer(this);
}

std::unique_ptr<char[]>&&
core::InputBuffer::execCommand(std::string&& a_command) noexcept
{
    std::unique_lock lock(*m_data_mutex);
    util::Condvar exec_synch;
    Context context{.buffer = this, .exec_synch = &exec_synch};
    Command command(std::move(a_command), bufferReturn, &context);
    m_command = &command;
    lock.unlock();

    exec_synch.wait();
    return std::move(m_result);
}

std::optional<core::Command*>
core::InputBuffer::obtainCommand() noexcept
{
    std::optional<core::Command*> result;
    if (m_command)
    {
        result = m_command;
    }
    return result;
}

void
core::InputBuffer::bufferReturn(std::unique_ptr<char[]>&& a_buffer,
                                void* a_context) noexcept
{
    auto& context            = *static_cast<Context*>(a_context);
    context.buffer->m_result = std::move(a_buffer);
    context.exec_synch->notify();
    context.buffer->m_command = nullptr;
}
