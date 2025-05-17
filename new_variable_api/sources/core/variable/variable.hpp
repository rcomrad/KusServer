#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/command/command.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct Variable
{
    std::string_view name;
    std::unordered_map<std::string_view, int> value_map;
    std::atomic<int> value;

    Variable() noexcept;
    Variable(const char* a_var_name,
             const char** a_values,
             int a_value_count) noexcept;
    Variable(const Variable& other) noexcept;

private:
    std::vector<std::string> value_array;
};

} // namespace core

//--------------------------------------------------------------------------------
