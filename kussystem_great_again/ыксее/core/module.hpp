#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "string/kus_string.hpp"

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

    static const str::String CALLBACK_VOLUME_SETUP;
    static const str::String CALLBACK_VOLUME_START;

    static void setupModules() noexcept;

private:
    std::unordered_map<str::String, ModuleSettings> mModules;
};
} // namespace core

//--------------------------------------------------------------------------------
