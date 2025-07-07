#include "variable.hpp"

#include "framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

core::Variable::get()
{
    KERNEL.getVariable(m_id);
}
