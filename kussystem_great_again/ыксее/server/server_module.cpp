#include "server_module.hpp"

#include "core/module.hpp"
#include "core/variable_storage.hpp"

#include "server.hpp"
#include "server_variable.hpp"

core::CallbackRegister serv::ServerModule::gServerModuleRegister(
    core::CallbackRegister::RegisterNode{
        core::Module::CALLBACK_VOLUME_SETUP, "server",
        (void*)serv::ServerModule::getModuleSettings});

core::Module::ModuleSettings
serv::ServerModule::getModuleSettings() noexcept
{
    return {serv::Server::start, registerVariables};
}

int
serv::ServerModule::getVatiable(int aVariableNum) noexcept
{
    return core::VariableStorage::get(getInstace().mVariableOffset +
                                      aVariableNum);
}

serv::ServerModule::ServerModule() noexcept : mVariableOffset(0)
{
}

serv::ServerModule&
serv::ServerModule::getInstace() noexcept
{
    static ServerModule instance;
    return instance;
}

void
serv::ServerModule::registerVariables() noexcept
{
    core::VariableSettings var;
    // TODO: merge string name and enum defenition
    var["token_state"]           = serv::ServerVariableHandlers::getTokenStatus;
    getInstace().mVariableOffset = core::VariableStorage::addSettings(var);
}
