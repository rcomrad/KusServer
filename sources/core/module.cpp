#include "module.hpp"

#include "module_registry.hpp"

core::Module::Module(const char* a_name) noexcept : m_name(a_name)
{
    ModuleRegistry::addModule(this);
}

void
core::Module::initialize() noexcept
{
    registerVariables();
}

void
core::Module::run() noexcept
{
}

void
core::Module::terminate() noexcept
{
}

void
core::Module::variableSetup(VariableInfoArray& a_set_array) noexcept
{
}

int
core::Module::getVatiable(int a_variable_num) noexcept
{
    return core::VariableStorage::get(m_variable_offset + a_variable_num);
}

void
core::Module::registerVariables() noexcept
{
    VariableInfoArray var;
    variableSetup(var);
    m_variable_offset = core::VariableStorage::addVariableInfo(var);
}
