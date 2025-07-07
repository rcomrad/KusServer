#include "variable.hpp"

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

int
core::Variable::get() const
{
    return KERNEL.getVariable(m_id);
}
