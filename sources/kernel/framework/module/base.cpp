#include "base.hpp"

#include "kernel/utility/synchronization/yield.hpp"

//--------------------------------------------------------------------------------

core::Base::Base()
{
    VariableStorage::init();
    CommandHandler::init();
    Printer::initer();

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
        execIfAvailable();
        makeModulesTick();
        util::Yield::small();
    }
    terminateModules();
}

void
core::Base::runWhileDoesSmth()
{
    size_t old_work = 1, cur_work = 1;
    while (isRunning() && old_work > 0)
    {
        old_work = cur_work;
        execIfAvailable();
        cur_work = makeModulesTick();
    }
    terminateModules();
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
