#include "int_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::IntVar::IntVar(const std::string& a_var_name) : Variable(a_var_name)
{
}

core::IntVar::IntVar(const std::string& a_var_name, int a_default_value)
    : Variable(a_var_name, a_default_value)
{
}

core::IntVar::IntVar(const std::string& a_var_name,
                     int a_min_value,
                     int a_max_value)
    : Variable(a_var_name, a_min_value, a_max_value)
{
}

core::IntVar::IntVar(const std::string& a_var_name,
                     int a_default_value,
                     int a_min_value,
                     int a_max_value)
    : Variable(a_var_name, a_default_value, a_min_value, a_max_value)
{
}
