#include "registry.hpp"

#include "utility/file_system/path_storage.hpp"

#include "state_storage.hpp"

SINGLETON_DEFINITOR(core, ModuleRegistry);

core::ModuleRegistry::ModuleRegistry() noexcept
{
    mainSetup();
}

void
core::ModuleRegistry::mainSetup() noexcept
{
}

void
core::ModuleRegistry::addModuleNonstatic(Module* a_module_ptr) noexcept
{
    m_module_storage.emplace_back(a_module_ptr);
}

bool
core::ModuleRegistry::isRunningNonstatic() noexcept
{
    // TODO: implement the real life cycle of the application
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
    StateStorage::apply();
}

void
core::ModuleRegistry::termModulesNonstatic() noexcept
{

    for (auto& i : m_apps)
    {
        i.join();
    }
}
