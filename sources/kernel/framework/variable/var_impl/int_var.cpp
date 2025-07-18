#include "int_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::IntVar::IntVar(const std::string& a_var_name)
{
    m_id = KERNEL.addVariableInfo(a_var_name);
}

core::IntVar::IntVar(const std::string& a_var_name,
                     int a_min_value,
                     int a_max_value)
{
    m_id = KERNEL.addVariableInfo(a_var_name, a_min_value, a_max_value);
}

void
core::IntVar::setVariable(int a_value)
{
    KERNEL.setVariable(m_id, a_value);
}
