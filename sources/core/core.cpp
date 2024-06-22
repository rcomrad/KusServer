#include "core.hpp"

#include "callback_storage.hpp"
#include "command_handler.hpp"
#include "logging.hpp"
#include "module.hpp"
#include "variable_storage.hpp"

//--------------------------------------------------------------------------------

core::Core::Core() noexcept
{
}

core::Core&
core::Core::getInstance() noexcept
{
    static Core instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
core::Core::setup() noexcept
{
    getInstance().setupNonstatic();
}

void
core::Core::setupNonstatic() noexcept
{
    Logging::setLogLevel(Logging::LogLevel::INFO);
    Logging::setOutputType(Logging::OutputType::FILE, "kuslog.txt");

    VariableStorage::addSettings({
        {"running_flag", nullptr}
    });
    Module::setupModules();
    VariableStorage::reloadSettings();
    VariableStorage::set(0, 1);

    auto modules =
        CallbackStorage::getVolumeCallbacks(Module::CALLBACK_VOLUME_START);
    for (const auto& i : modules)
    {
        const auto& module_name = i.first;
        Module::FPModuleActions module_callback =
            (Module::FPModuleActions)i.second;
        mApps[module_name] = std::move(std::thread(module_callback));
    }
    mApps["command_scanner"] =
        std::move(std::thread(CommandHandler::scanCommand));
}

//--------------------------------------------------------------------------------

void
core::Core::run() noexcept
{
    getInstance().runNonstatic();
}

void
core::Core::runNonstatic() noexcept
{
    while (VariableStorage::get(0))
    {
        CommandHandler::handlCommand();
    }
}

//--------------------------------------------------------------------------------
