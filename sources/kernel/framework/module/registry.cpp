#include "registry.hpp"

//--------------------------------------------------------------------------------

#include "kernel/utility/common/exception.hpp"

#include "module.hpp"
#include "register.hpp"

//--------------------------------------------------------------------------------

core::ModuleRegistry::ModuleRegistry() noexcept
    : m_is_started(false), m_alive_count(0)
{
    reloadModules();
}

void
core::ModuleRegistry::init()
{
}

void
core::ModuleRegistry::reloadModules()
{
    if (m_is_started)
    {
        THROW("Modules can't be reloaded, they are already running.")
    }
    m_modules = std::move(global_modules);
}

//--------------------------------------------------------------------------------

size_t
core::ModuleRegistry::makeModulesTick()
{
    size_t result = 0;
    for (auto& i : m_modules)
    {
        result += i->execute() ? 1 : 0;
    }
    return m_alive_count = result; // TODO: command for print value
}

void
core::ModuleRegistry::terminateModules()
{
    int cnt = 1;
    while (cnt)
    {
        cnt = 0;
        for (auto& i : m_modules)
        {
            i->close();
            cnt += i->execute() ? 1 : 0;
        }
    }
}

//--------------------------------------------------------------------------------
