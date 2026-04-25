#include "bool_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::BoolVar::BoolVar(const std::string& a_var_name)
    : Variable(true, a_var_name)
{
}
