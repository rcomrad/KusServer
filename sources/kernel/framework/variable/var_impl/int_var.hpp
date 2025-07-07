#pragma once

//--------------------------------------------------------------------------------

#include <string>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct IntVar : public Variable
{
public:
    IntVar(const std::string& a_var_name);
    IntVar(const std::string& a_var_name, int a_min_value, int a_max_value);
    void setVariable(int a_value);
};

} // namespace core

//--------------------------------------------------------------------------------
