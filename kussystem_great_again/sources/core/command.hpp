#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
struct Command
{
    enum
    {
        COMMAND_MAX_SIZE = 40
    };

    HOLY_TRINITY_NOCOPY(Command);

    std::atomic<bool> ready;
    char buffer[COMMAND_MAX_SIZE];
    std::string_view value;
    std::unordered_set<std::string_view> arguments;
    std::unordered_map<std::string_view, std::string_view> variables;

    Command() noexcept;
    void assemble() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
