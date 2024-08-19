#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "core/logging/logging.hpp"

#include "utility/common/holy_trinity.hpp"

#include "definitions.hpp"

//--------------------------------------------------------------------------------

#define LOG_COMMAND_ERROR

struct CommandAssertResult
{
};

namespace core
{
struct Command
{
    HOLY_TRINITY_NOCOPY(Command);

    std::string_view value;
    std::vector<std::string_view> arguments;
    std::unordered_map<std::string_view, std::string_view> variables;
    std::unique_ptr<char[]> m_result_buffer;

    Command(std::string&& aStr,
            FP_ResultCallback a_outp_call,
            void* a_context = nullptr) noexcept;

    ~Command() noexcept;

    void callResultFunc() noexcept;

private:
    // real (unparsed) command string
    std::string m_data;

    // data for return command result
    void* m_context;
    FP_ResultCallback m_output_callback;
};
} // namespace core

//--------------------------------------------------------------------------------
