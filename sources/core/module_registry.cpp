#include "module_registry.hpp"

SINGLETON_DEFINITOR(core, ModuleRegistry);

void
core::ModuleRegistry::addModuleNonstatic(Module* a_module_ptr) noexcept
{
    m_module_storage.emplace_back(a_module_ptr);
}

void
core::ModuleRegistry::initModulesNonstatic() noexcept
{
    for (auto& i : m_module_storage)
    {
        i->trigger_initialization();
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
