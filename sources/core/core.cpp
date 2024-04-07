#include "core.hpp"

#include "callback_storage.hpp"
#include "logging.hpp"

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

    auto modules = CallbackStorage::getVolumeCallbacks(
        CallbackStorage::MODULE_CALLBACK_VOLUME);
    for (const auto& i : modules)
    {
        auto& module_name     = i.first;
        void* module_callback = i.second;
        // TODO: do we need move?
        mApps[module_name] = std::move(std::thread((void (*)()) module_callback));
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
