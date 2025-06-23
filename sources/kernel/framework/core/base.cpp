#include "base.hpp"

#include "kernel/framework/logger/include_me.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

//--------------------------------------------------------------------------------

core::Base::Base()
{
    VariableStorage::init();
    CommandHandler::init();
    core::LocalLogger::getLogger().redirectDefault("main");

    m_is_running_var_num = addBoolVariable("is_running");
    setVariable(m_is_running_var_num, true);

    ModuleRegistry::init();
}

core::Base::~Base()
{
    stop();
}

void
core::Base::run()
{
    while (isRunning())
    {
        doWork();
        util::Sleep::yield();
    }
    terminateModules();
}

bool
core::Base::doWork()
{
    bool result = false;
    result |= execIfAvailable();
    result |= makeModulesTick();
    return result;
}

bool
core::Base::isRunning() const
{
    return getVariable(m_is_running_var_num);
}

void
core::Base::stop()
{
    setVariable(m_is_running_var_num, false);
}

void
core::Base::listenSTDIN() noexcept
{
    m_stdin.create();
}

//--------------------------------------------------------------------------------
