#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"
#include "logging.hpp"

//--------------------------------------------------------------------------------

#define LOG_COMMAND_ERROR

namespace core
{
struct Command
{
    using OutputCallback = void (*)(const char*) noexcept;

    HOLY_TRINITY_NOCOPY(Command);

    str::string value;
    std::vector<str::string> arguments;
    std::unordered_map<str::string, str::string> variables;

    Command(const str::string& aStr, OutputCallback a_outp_call) noexcept;

    void setResultBufferSize(size_t a_result_buffer_size) noexcept;
    size_t getResultBufferSize() noexcept;
    // void returnMsg() noexcept;
    // void returnError() noexcept;

    char* getResultBuffer() noexcept;
    void callOutputFunc() noexcept;

    std::optional<int> getArgumentAsNumber(int a_num) noexcept;

private:
    OutputCallback m_output_callback;
    size_t m_result_buffer_size;
    std::unique_ptr<char[]> m_result_buffer;
};
} // namespace core

#define WRITE_LOG_MSG_CMD(cmd, type, format, ...)                           \
    WRITE_LOG_MSG(cmd.getResultBuffer(), cmd.getResultBufferSize(), format, \
                  #type, __VA_ARGS__)

#define COMMAND_RETURN_MSG(cmd, ...) WRITE_LOG_MSG_CMD(cmd, CMD, __VA_ARGS__)
#define COMMAND_RETURN_ERROR(cmd, ...) \
    WRITE_LOG_MSG_CMD(cmd, ERROR, __VA_ARGS__)

#define COMMAND_HANDLER(name) static void name(Command& aCommand) noexept;
#define COMMAND_HANDLER_NONSTATIC(name) \
    SINGL_PRIV_VOID_METHOD(name, (core::Command & aCommand))

#define ARGUMENT_SIZE_CHECK(num)                                             \
    if (aCommand.arguments.size() != num)                                    \
    {                                                                        \
        COMMAND_RETURN_ERROR(                                                \
            aCommand,                                                        \
            "Incorrect number of arguments. Expected %d arguments, got %lu", \
            num, aCommand.arguments.size());                                 \
        return;                                                              \
    }

#define GET_ARG_AS_NUM(name, num)                             \
    auto optional_##name = aCommand.getArgumentAsNumber(num); \
    if (!optional_##name.has_value())                         \
    {                                                         \
        return;                                               \
    }                                                         \
    int name = optional_##name.value();

//--------------------------------------------------------------------------------
