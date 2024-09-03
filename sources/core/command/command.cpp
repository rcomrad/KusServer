#include "command.hpp"

#include "core/logging/logging.hpp"

core::Command::Command(std::string&& a_comm_str,
                       FP_ResultCallback a_outp_call,
                       void* a_context) noexcept
    : CommandData(std::move(a_comm_str)),
      m_is_call_result_func(false),
      m_output_callback(a_outp_call),
      m_context(a_context)
{
}

core::Command::~Command()
{
    callResultFunc();
}

void
core::Command::callResultFunc() noexcept
{
    if (m_output_callback == nullptr)
    {
        LOG_ERROR("Command output callback dosn't set");
        return;
    }
    if (m_is_call_result_func)
    {
        return;
    }
    m_output_callback(std::move(m_result_buffer), m_context);
    m_is_call_result_func = true;
}

bool
core::Command::execResultIsError() const noexcept
{
    bool result = true;
    if (m_result_buffer.get() != nullptr)
    {
        result = m_result_buffer[1] == 'E';
    }
    return result;
}
