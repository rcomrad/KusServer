#include "module.hpp"

#include "core/logging/logging.hpp"

#include "registry.hpp"

core::Module::Module(const char* a_name) noexcept : m_name(a_name)
{
    ModuleRegistry::addModule(this);
}

//------------------------------------------------------------------------------
// Module interacting interface
//------------------------------------------------------------------------------

void
core::Module::init() noexcept
{
    LOG_INFO("Begin '%s' module initialization.", m_name);
    commandSetup();
    variableSetup();
    initialize();
    LOG_INFO("      '%s' module initialization finished.", m_name);
}

void
core::Module::term() noexcept
{
    LOG_INFO("Begin '%s' module termination.", m_name);
    terminate();
    LOG_INFO("     '%s' module termination finished.", m_name);
}

void
core::Module::run() noexcept
{
    LOG_INFO("Start '%s' module", m_name);
    while (ModuleRegistry::isRunning())
    {
        if (!loopBody())
        {
            break;
        }
    }
    LOG_INFO("      '%s' module finished.", m_name);
}

//------------------------------------------------------------------------------
// Module real life-cycle methods
//------------------------------------------------------------------------------

void
core::Module::initialize() noexcept
{
}

void
core::Module::terminate() noexcept
{
}

bool
core::Module::loopBody() noexcept
{
    return false;
}

//------------------------------------------------------------------------------
// Methods for module setup
//------------------------------------------------------------------------------

void
core::Module::commandSetup() const noexcept
{
}

void
core::Module::variableSetup() const noexcept
{
}

//------------------------------------------------------------------------------
// Module variables handlers
//------------------------------------------------------------------------------

void
core::Module::setVariable(int a_variable_num,
                          int a_variable_value) const noexcept
{
    core::VariableStorage::set(m_variable_offset + a_variable_num,
                               a_variable_value);
}

int
core::Module::getVariable(int a_variable_num) const noexcept
{
    return core::VariableStorage::get(m_variable_offset + a_variable_num);
}

//------------------------------------------------------------------------------

void
core::Module::registerVariable(const char* a_var_name,
                               const char** a_values,
                               int a_value_count) const noexcept
{
    m_variable_offset =
        VariableRegister::registerVariable(a_var_name, a_values, a_value_count);
}

void
core::Module::registerVariable(
    VariableInfoArray&& a_var_data_array) const noexcept
{
    m_variable_offset =
        VariableRegister::registerVariable(std::move(a_var_data_array));
}
