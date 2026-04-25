#include "enum_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::EnumVar::EnumVar(const std::string& a_var_name,
                       const std::vector<std::string>& a_values)
    : Variable(a_var_name, a_values)
{
}
