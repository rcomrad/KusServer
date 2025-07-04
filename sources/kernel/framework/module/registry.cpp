#include "registry.hpp"

//--------------------------------------------------------------------------------

#include "kernel/framework/command/state_storage.hpp"
#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"

#include "constructor.hpp"
#include "module.hpp"
#include "thread_module.hpp"

//--------------------------------------------------------------------------------

core::ModuleRegistry::ModuleRegistry() noexcept : m_alive_count(0)
{
}

void
core::ModuleRegistry::init()
{
    registrateBaseCommand("mod_add",
                          "Creates a module with the specified name.",
                          "[module_name]...");
    registrateBaseCommand(
        "mod_list",
        "Displays a list of all available modules and their current status.");
    registrateBaseCommand(
        "mod_info", "Displays the state history for the specified module.",
        "module_name");
    registrateBaseCommand("mod_all", "Displays all registered modules.");
    registrateBaseCommand("mod_active_count",
                          "Displays the number of currently active modules.");

    KERNEL.listenCommand("mod_add", StateStorage::StateType::MERGE_ARGS);
}

//--------------------------------------------------------------------------------

bool
core::ModuleRegistry::makeModulesTick()
{
    int result = 0;
    for (auto& i : m_modules)
    {
        result += i->execute() ? 1 : 0;
        auto thread_ptr = dynamic_cast<ThreadModule*>(i.get());
        if (thread_ptr && thread_ptr->isRunning())
        {
            result += 1;
        }
    }
    return static_cast<bool>(m_alive_count = result);
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

void
core::ModuleRegistry::modAdd(core::Command& a_command)
{
    a_command.noVars();

    // TODO: empty?
    for (const auto& name : a_command.arguments)
    {
        auto module_ptr = ModuleConstructor::getInstance().construct(name);
        if (module_ptr == nullptr)
        {
            return;
        }
        m_modules.emplace_back(std::move(module_ptr));
    }

    LOG_CMD("Modules created successfully.");
}

void
core::ModuleRegistry::modList(core::Command& a_command)
{
    a_command.noVars().noArgs();
    LOG_CMD("%s", buildTable());
}

void
core::ModuleRegistry::modInfo(core::Command& a_command)
{
    LOG_EXEPT("NOT IMPLEMENTED");
}

void
core::ModuleRegistry::modAll(core::Command& a_command)
{
    LOG_EXEPT("NOT IMPLEMENTED");
}

void
core::ModuleRegistry::modActiveCount(core::Command& a_command)
{
    a_command.noVars().noArgs();
    LOG_CMD("%d", m_alive_count);
}

//------------------------------------------------------------------------------

void
core::ModuleRegistry::print() const
{
    getKeyInfo().alignmentRight().setSeparator('|');
    setDefaultSeparator(' ');
    addTableConrainer(m_modules);
}

//--------------------------------------------------------------------------------
