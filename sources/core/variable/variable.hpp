#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <optional>
#include <string>
#include <vector>

#include "core/command/command.hpp"

//--------------------------------------------------------------------------------

namespace core
{

using FPVariableParser = std::optional<int> (*)(const std::string_view&);
#define VARIABLE_PARSER(name) \
    static std::optional<int> name(const std::string_view& a_value) noexcept;

struct Variable
{
    std::string name;
    std::vector<std::string> possable_values;
    std::atomic<int> value;
    FPVariableParser parser;

    Variable() noexcept;
    Variable(std::string&& a_name,
             FPVariableParser a_parser,
             std::vector<std::string>&& a_possable_values) noexcept;
    Variable(const Variable& other) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
