#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <vector>

#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct EnumVar : public Variable<std::string_view>
{
public:
    EnumVar(const std::string& a_var_name,
            const std::vector<std::string>& a_values);
};

} // namespace core

//--------------------------------------------------------------------------------
