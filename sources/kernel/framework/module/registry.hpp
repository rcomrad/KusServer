#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <memory>
#include <vector>

#include "kernel/framework/command/command_caller.hpp"
#include "kernel/framework/logger/table/include_me.hpp"

#include "module.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class ModuleRegistry : public CommandCaller, public TablePrinter
{
public:
    ModuleRegistry() noexcept;
    ~ModuleRegistry() = default;

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
