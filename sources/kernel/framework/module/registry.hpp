#pragma once

//--------------------------------------------------------------------------------

// #include <atomic>
// #include <vector>
#include <memory>
#include <vector>

#include "module.hpp"

// #include "kernel/utility/synchronization/condvar.hpp"

// #include "module_interface.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class ModuleRegistry
{
public:
    ModuleRegistry() noexcept;
    ~ModuleRegistry() = default;
    void reloadModules();
    

    // void exec();
    // void cloaseApp() noexcept;
    // void addModule(Module* a_module_ptr);

protected:
    void init();
    size_t makeModulesTick();
    void terminateModules();

private:
    bool m_is_started;
    size_t m_alive_count;
    std::vector<std::unique_ptr<Module>> m_modules;
    // util::Condvar m_all_closed;
    // std::atomic<bool> m_app_is_working;

    // std::vector<Module*> m_modules;
    // std::vector<Module::TaskFP> m_tasks;
};

} // namespace core

//--------------------------------------------------------------------------------
