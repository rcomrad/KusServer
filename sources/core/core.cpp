#include "core.hpp"

#include "callback_storage.hpp"
#include "logging.hpp"
#include "module.hpp"

//--------------------------------------------------------------------------------

core::Core::Core() noexcept : mAppIsTurnedOn(true)
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
    Logging::setLogLevel(Logging::LogLevel::Info);
    Logging::setOutputType(Logging::OutputType::File, "kuslog.txt");

    core::Module::setupModules();
    core::VariableStorage::reloadSettings();

    auto modules = CallbackStorage::getVolumeCallbacks(
        Module::CALLBACK_VOLUME_MODULE_START);
    for (const auto& i : modules)
    {
        const auto& module_name = i.first;
        Module::FPModuleActions module_callback =
            (Module::FPModuleActions)i.second;
        mApps[module_name] = std::move(std::thread(module_callback));
    }
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
    while (mAppIsTurnedOn)
    {
    }
}

//--------------------------------------------------------------------------------
