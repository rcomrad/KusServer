#pragma once

//--------------------------------------------------------------------------------

#include <thread>
#include <unordered_map>
#include <vector>

#include "utility/common/holy_trinity.hpp"

#include "module.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class ModuleRegistry
{
public:
    HOLY_TRINITY_SINGLETON(ModuleRegistry);

    SINGL_VOID_METHOD(addModule, (Module * a_module_ptr))

    SINGL_VOID_METHOD(initModules, ());
    SINGL_VOID_METHOD(runModules, ());
    SINGL_VOID_METHOD(termModules, ());

    SINGL_RET_METHOD(bool, isRunning, ());

private:
    std::vector<Module*> m_module_storage;
    std::vector<std::thread> m_apps;

    ModuleRegistry() noexcept;
    void mainSetup() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
