#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <vector>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class VariableRegister
{
protected:
    struct Info
    {
        std::string var_name;
        FPVariableParser parse_func;
        std::vector<std::string> possable_values;
    };
    using VariableInfoArray = std::vector<core::VariableRegister::Info>;

    static int registerVariable(
        std::string&& a_var_name,
        FPVariableParser a_parse_func,
        std::vector<std::string>&& a_possable_values) noexcept;
    static int registerVariable(VariableInfoArray&& a_var_data_array) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
