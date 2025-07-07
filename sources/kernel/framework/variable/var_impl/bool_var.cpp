#include "bool_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::BoolVar::BoolVar(const std::string& a_var_name)
{
    m_id = KERNEL.addBoolVariable(a_var_name);
}

void
core::BoolVar::setVariable(bool a_value)
{
    KERNEL.setVariable(m_id, a_value);
}
