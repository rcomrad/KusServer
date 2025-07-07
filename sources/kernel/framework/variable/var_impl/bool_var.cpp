#include "bool_var.hpp"

#include "framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::BoolVar::BoolVar(const std::string& a_var_name,
                       const std::vector<std::string>& a_values)
{
    m_id = KERNEL.addVariableInfo(a_var_name, a_values);
}

void
core::BoolVar::setVariable(bool a_value)
{
    KERNEL.setVariable(m_id, a_value);
}
