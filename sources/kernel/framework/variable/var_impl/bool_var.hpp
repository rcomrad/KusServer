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
    BoolVar(const std::string& a_var_name);
};

} // namespace core

//--------------------------------------------------------------------------------
