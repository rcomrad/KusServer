#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <vector>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct EnumVar : public Variable
{
public:
    EnumVar(const std::string& a_var_name,
            const std::vector<std::string>& a_values);
    void setVariable(std::string_view a_value);
};

} // namespace core

//--------------------------------------------------------------------------------
