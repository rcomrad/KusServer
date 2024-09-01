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
        const char* var_name;
        const char** values;
        int value_count;
    };
    using VariableInfoArray = std::vector<core::VariableRegister::Info>;

    static int registerVariable(const char* a_var_name,
                                const char** a_values,
                                int a_value_count) noexcept;
    static int registerVariable(VariableInfoArray&& a_var_data_array) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
