#include "constructor.hpp"

#include "kernel/framework/logger/include_me.hpp"

core::ModuleConstructor::ModuleConstructor()
{
}

core::ModuleConstructor&
core::ModuleConstructor::getInstance()
{
    static ModuleConstructor instance;
    return instance;
}

void
core::ModuleConstructor::add(const std::string& a_name,
                             ModuleConstructorFunc a_func) noexcept
{
    m_functors[a_name] = a_func;
}

core::ModuleConstructor::ModuleType
core::ModuleConstructor::construct(const std::string& a_name)
{
    ModuleType result;
    auto it = m_functors.find(a_name);
    if (it != m_functors.end())
    {
        result = it->second();
    }
    else
    {
        LOG_ERROR("Can't construct module with name '%s'. No such module.",
                  a_name);
    }
    return result;
}

void
core::ModuleConstructor::print() const
{
    addTableConrainer(m_functors);
}
