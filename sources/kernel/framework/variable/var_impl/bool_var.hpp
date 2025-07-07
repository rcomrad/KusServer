#pragma once

//--------------------------------------------------------------------------------

#include <string>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct BoolVar : public Variable
{
public:
    BoolVar(const std::string& a_var_name);
    void setVariable(bool a_value);
};

} // namespace core

//--------------------------------------------------------------------------------
