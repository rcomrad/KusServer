#include "bool_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::BoolVar::BoolVar(const std::string& a_var_name, bool a_value)
    : Variable(a_value, a_var_name)
{
}
