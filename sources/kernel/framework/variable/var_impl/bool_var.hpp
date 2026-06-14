#pragma once

//--------------------------------------------------------------------------------

#include <string>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct BoolVar : public Variable<bool>
{
public:
    BoolVar(const std::string& a_var_name, bool a_value = true);
};

} // namespace core

//--------------------------------------------------------------------------------
