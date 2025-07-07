#include "enum_var.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::EnumVar::EnumVar(const std::string& a_var_name,
                       const std::vector<std::string>& a_values)
{
    m_id = KERNEL.addVariableInfo(a_var_name, a_values);
}

void
core::EnumVar::setVariable(std::string_view a_value)
{
    KERNEL.setVariable(m_id, a_value);
}
