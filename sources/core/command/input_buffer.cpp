#include "input_buffer.hpp"

#include "registry.hpp"

core::InputBuffer::InputBuffer() noexcept : m_command(nullptr)
{
    CommandHandler::listen(this);
}

core::InputBuffer::~InputBuffer() noexcept
{
    CommandHandler::unlisten(this);
}

std::unique_ptr<char[]>&&
core::InputBuffer::execCommand(std::string&& a_command) noexcept
{
    m_data_mutex.lock();
    Condvar exec_synch;
    Context context{.buffer = this, .exec_synch = &exec_synch};
    CommandExtend command(std::move(a_command), bufferReturn, &context);
    m_command = &command;
    m_data_mutex.unlock();

    exec_synch.wait();
    return std::move(m_result);
}

std::optional<core::CommandExtend*>
core::InputBuffer::obtainCommand() noexcept
{
    std::lock_guard<std::mutex> lock(m_data_mutex);

    std::optional<core::CommandExtend*> result;
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
