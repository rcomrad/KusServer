#include "kernel.hpp"

//--------------------------------------------------------------------------------

util::LifecycleManager<core::Kernel> core::Kernel::m_self_ptr;

void
core::Kernel::create()
{
    m_self_ptr.create();
}

void
core::Kernel::destroy() noexcept
{
    m_self_ptr.destroy();
}

core::Kernel&
core::Kernel::getInstance() noexcept
{
    return m_self_ptr.obj;
}

//--------------------------------------------------------------------------------
