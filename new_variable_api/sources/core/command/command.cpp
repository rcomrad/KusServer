#include "command.hpp"

#include "utility/string/slicer.hpp"

core::Command::Command(std::string&& aStr,
                       FP_ResultCallback a_outp_call,
                       void* a_context) noexcept
    : m_output_callback(a_outp_call), m_context(a_context)
{
    m_data    = std::move(aStr);
    auto args = util::Slicer::process(m_data, "; \n\t");

    // first word is a command and processed separately
    value = args[0];

    for (int i = 1; i < args.size(); ++i)
    {
        auto temp = util::Slicer::process(args[i], "=");
        if (temp.size() == 1)
        {
            arguments.emplace_back(temp[0]);
        }
        else
        {
            variables[temp[0]] = temp[1];
        }
    }
}

core::Command::~Command() noexcept
{
}

//------------------------------------------------------------------------------

void
core::Command::callResultFunc() noexcept
{
    if (m_output_callback == nullptr)
    {
        LOG_ERROR("Command output callback dosn't set");
        return;
    }
    m_output_callback(std::move(m_result_buffer), m_context);
}
