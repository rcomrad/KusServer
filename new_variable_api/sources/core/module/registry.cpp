#include "registry.hpp"

SINGLETON_DEFINITOR(core, ModuleRegistry);

void
core::ModuleRegistry::addModuleNonstatic(Module* a_module_ptr) noexcept
{
    m_module_storage.emplace_back(a_module_ptr);
}

bool
core::ModuleRegistry::isRunningNonstatic() noexcept
{
    // TODO: life-cycle
    return true;
}

void
core::ModuleRegistry::initModulesNonstatic() noexcept
{
    for (auto& i : m_module_storage)
    {
        i->init();
    }
}

void
core::ModuleRegistry::runModulesNonstatic() noexcept
{
    for (auto& i : m_module_storage)
    {
        m_apps.emplace_back(&Module::run, i);
    }
}

void
core::ModuleRegistry::termModulesNonstatic() noexcept
{

    for (auto& i : m_apps)
    {
        i.join();
    }
}
