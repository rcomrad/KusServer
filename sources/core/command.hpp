#pragma once

//--------------------------------------------------------------------------------

#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
struct Command
{
    HOLY_TRINITY_NOCOPY(Command);

    bool ready;
    char buffer[40];
    std::string_view value;
    std::unordered_set<std::string_view> arguments;
    std::unordered_map<std::string_view, std::string_view> variables;

    Command() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
