#include "command.hpp"

#include "string/parser.hpp"

core::Command::Command(const str::string& aStr,
                       OutputCallback a_outp_call) noexcept
    : m_result_buffer_size(200), m_output_callback(a_outp_call)
{
    auto args = str::Parser::slice(aStr, (char*)aStr.c_str(), "; \n\t");
    value     = args[0];
    args.erase(args.begin());

    for (auto& i : args)
    {
        // TODO: empty line slice bug
        auto temp = str::Parser::slice(i, std::string(i).data(), "=");
        if (temp.size() == 1)
        {
            arguments.insert(arguments.end(), str::string(temp[0]));
        }
        else
        {
            variables[str::string(temp[0])] = temp[1];
        }
    }
}

void
core::Command::setResultBufferSize(size_t a_result_buffer_size) noexcept
{
    m_result_buffer_size = a_result_buffer_size;
}

size_t
core::Command::getResultBufferSize() noexcept
{
    return m_result_buffer_size;
}

// void
// core::Command::returnMsg() noexcept
// {
//     prepareResultBuffer();

// }

// void
// core::Command::returnError() noexcept
// {
//     prepareResultBuffer();
//     WRITE_LOG_MSG
// }

// void
// core::Command::prepareResultBuffer() noexcept
// {
//     if (!m_result_buffer)
//     {
//         m_result_buffer = std::make_unique<char[]>(m_result_buffer_size);
//     }
// }

char*
core::Command::getResultBuffer() noexcept
{
    if (!m_result_buffer)
    {
        m_result_buffer = std::make_unique<char[]>(m_result_buffer_size);
    }
    return m_result_buffer.get();
}

void
core::Command::callOutputFunc() noexcept
{
    if (m_output_callback == nullptr)
    {
        LOG_ERROR("Command output callback dosn't set");
        return;
    }
    if (strlen(m_result_buffer.get()) >= getResultBufferSize())
    {
        int expected = getResultBufferSize();
        int received = strlen(m_result_buffer.get());

        // m_result_buffer.get()[0] = 0;
        // m_result_buffer.reset(nullptr);

        // setResultBufferSize(720);

        COMMAND_RETURN_ERROR((*this),
                             "ERROR: COMMAND OUPUT TOO LARGE! "
                             "Expected len no more then '%d', received '%d'",
                             expected, received);
    }
    m_output_callback(m_result_buffer.get());
}

std::optional<int>
core::Command::getArgumentAsNumber(int a_num) noexcept
{
    std::optional<int> result;
    try
    {
        result = std::stoi(arguments[a_num]);
    }
    catch (const std::exception& e)
    {
        Command& aCommand = *this;
        COMMAND_RETURN_ERROR(
            aCommand, "Unable to parse credential number, exception '%s'",
            e.what());
    }
    return result;
}
