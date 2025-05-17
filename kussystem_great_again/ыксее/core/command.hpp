#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>
#include <unordered_set>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
struct Command
{
    HOLY_TRINITY_NOCOPY(Command);

    str::String value;
    // std::unordered_set<str::String> arguments;
    // std::unordered_map<str::String, str::String> variables;

    Command(const char* aStr) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
