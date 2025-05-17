#pragma once

//--------------------------------------------------------------------------------

#include "core/callback_register.hpp"
#include "core/holy_trinity.hpp"
#include "core/module.hpp"

//--------------------------------------------------------------------------------

namespace serv
{
class ServerModule
{
public:
    static core::Module::ModuleSettings getModuleSettings() noexcept;
    static int getVatiable(int aVariableNum) noexcept;

private:
    int mVariableOffset;
    static core::CallbackRegister gServerModuleRegister;

    HOLY_TRINITY_NOCOPY(ServerModule);
    ServerModule() noexcept;
    static ServerModule& getInstace() noexcept;

    static void registerVariables() noexcept;
};
} // namespace serv

//--------------------------------------------------------------------------------
