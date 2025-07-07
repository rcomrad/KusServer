#include "enum_var.hpp"

#include "framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::EnumVar::EnumVar(const std::string& a_var_name)
{
    m_id = KERNEL.addBoolVariable(a_var_name);
}

void
core::EnumVar::setVariable(std::string_view a_value)
{
    KERNEL.setVariable(m_id, a_value);
}
