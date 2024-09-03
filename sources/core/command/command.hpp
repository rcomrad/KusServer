#pragma once

//--------------------------------------------------------------------------------

#include <memory>

#include "utility/common/holy_trinity.hpp"

#include "command_data.hpp"
#include "definitions.hpp"

//--------------------------------------------------------------------------------

namespace core
{
struct Command : public CommandData
{
    HOLY_TRINITY_NOCOPY(Command);

    std::unique_ptr<char[]> m_result_buffer;

    Command(std::string&& a_comm_str,
            FP_ResultCallback a_outp_call,
            void* a_context = nullptr) noexcept;

    ~Command() noexcept;

    void callResultFunc() noexcept;

    bool execResultIsError() const noexcept;

private:
    bool m_is_call_result_func;

    // data for return command result
    void* m_context;
    FP_ResultCallback m_output_callback;
};
} // namespace core

//--------------------------------------------------------------------------------
