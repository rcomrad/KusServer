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

    str::string value;
    std::unordered_set<str::string> arguments;
    std::unordered_map<str::string, str::string> variables;

    Command(const str::string& aStr) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
