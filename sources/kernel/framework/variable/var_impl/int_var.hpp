#pragma once

//--------------------------------------------------------------------------------

#include <string>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct IntVar : public Variable<int>
{
public:
    IntVar(const std::string& a_var_name);
    IntVar(const std::string& a_var_name, int a_default_value);
    IntVar(const std::string& a_var_name, int a_min_value, int a_max_value);
    IntVar(const std::string& a_var_name,
           int a_default_value,
           int a_min_value,
           int a_max_value);
};

} // namespace core

//--------------------------------------------------------------------------------
