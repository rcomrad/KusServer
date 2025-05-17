#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "kus_standard/hash_map_by_str.hpp"

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Module
{
public:
    typedef void (*FPModuleActions)();

    HOLY_TRINITY_SINGLE(Module);

    struct ModuleSettings
    {
        FPModuleActions mModuleLoppFunc;
        FPModuleActions mVariableRegister;
    };

    inline static const char CALLBACK_VOLUME_SETUP[] = "module_setup";
    inline static const char CALLBACK_VOLUME_START[] = "module_start";

    static void setupModules() noexcept;

private:
    HAS_MAP_BY_STR(m_modules, Modules, 200, ModuleSettings);
};
} // namespace core

//--------------------------------------------------------------------------------
