#include "core.hpp"

#include "command_handler.hpp"
#include "logging.hpp"
#include "module_registry.hpp"
#include "variable_storage.hpp"
#include "yield.hpp"

SINGLETON_DEFINITOR(core, Core);

void
core::Core::setupNonstatic() noexcept
{
    Logging::setLogLevel(Logging::LogLevel::INFO);
    Logging::setOutputType(Logging::OutputType::FILE, "kuslog.txt");

    VariableStorage::addVariableInfo(VariableInfoArray{
        {"running_flag", nullptr}
    });
    ModuleRegistry::initModules();
    VariableStorage::reloadValuesFromFile();
    VariableStorage::set(0, 1);
}

void
core::Core::runNonstatic() noexcept
{
    ModuleRegistry::runModules();
    while (isRunning())
    {
        CommandHandler::handlCommand();
        Yield::large();
    }
}

bool
core::Core::isRunningNonstatic() noexcept
{
    return VariableStorage::get(0);
}
