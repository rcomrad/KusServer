#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <memory>
#include <ranges>
#include <vector>

#include "kernel/framework/command/command_caller.hpp"
#include "kernel/framework/logger/include_me.hpp"

#include "module.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class ModuleRegistry : public CommandCaller, public TablePrinter
{
public:
    ModuleRegistry() noexcept;
    ~ModuleRegistry() = default;

    template <typename ModuleT>
    ModuleT& getModuleRef(std::string_view a_name)
    {
        auto it = std::ranges::find_if(m_modules,
                                       [&a_name](std::unique_ptr<Module>& a_ptr)
                                       { return a_ptr->getName() == a_name; });
        if (it == m_modules.end())
        {
            THROW("No such module");
        }
        return *static_cast<ModuleT*>(it->get());
    }

protected:
    void init();
    bool makeModulesTick();
    void terminateModules();

private:
    std::atomic<int> m_alive_count;
    std::vector<std::unique_ptr<Module>> m_modules;

    COMMAND_HANDLER(modAdd, 0);
    COMMAND_HANDLER(modList, 1);
    COMMAND_HANDLER(modInfo, 2);
    COMMAND_HANDLER(modAll, 3);
    COMMAND_HANDLER(modActiveCount, 4);

    void print() const final;
};

} // namespace core

//--------------------------------------------------------------------------------
