#pragma once

//--------------------------------------------------------------------------------

#include <memory>

#include "kernel/utility/common/holy_trinity.hpp"

#include "command_data.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandFunctor : public CommandData
{
private:
    using FP_ResultCallback = void (*)(std::unique_ptr<char[]>&&,
                                       void*) noexcept;

public:
    HOLY_TRINITY_NOCOPY(CommandFunctor);

    std::unique_ptr<char[]> m_result_buffer;

    CommandFunctor(std::string&& a_comm_str,
                   FP_ResultCallback a_outp_call,
                   void* a_context = nullptr) noexcept;

    ~CommandFunctor() noexcept;

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
