#include "thread_module_interface.hpp"

//------------------------------------------------------------------------------

#include "thread_module.hpp"

//------------------------------------------------------------------------------

core::ThreadModuleInterface::ThreadModuleInterface(
    const std::string& a_name,
    ThreadModule& a_thread_mpdule_ref)
    : Module(a_name), m_thread_module_ref(a_thread_mpdule_ref)
{
}

//------------------------------------------------------------------------------
// Module body
//------------------------------------------------------------------------------

void
core::ThreadModuleInterface::initialize()
{
    m_thread_module_ref.threadInitialize();
}

bool
core::ThreadModuleInterface::loopBody()
{
    return m_thread_module_ref.threadLoopBody();
}

void
core::ThreadModuleInterface::terminate()
{
    m_thread_module_ref.threadTerminate();
}

//------------------------------------------------------------------------------
