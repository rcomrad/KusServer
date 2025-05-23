#include "thread_module.hpp"

//------------------------------------------------------------------------------

#include "kernel/framework/logger/include_me.hpp"
#include "kernel/framework/module/kernel.hpp"
#include "kernel/utility/synchronization/yield.hpp"

#include "module_func_try_block.hpp"

//------------------------------------------------------------------------------

core::ThreadModule::ThreadModule(const std::string& a_name)
    : Module(a_name),
      m_thread_module(a_name + "_thread", *this),
      m_is_running(true)
{
    useBaseSyncState(&m_sync_state);
    m_thread_module.useThreadSyncState(&m_sync_state);
    m_thread = std::thread(&ThreadModule::threadLoop, this);
}

core::ThreadModule::~ThreadModule()
{
    useBaseSyncState(nullptr);
    m_thread_module.useThreadSyncState(nullptr);
    m_thread.join();
}

//------------------------------------------------------------------------------
// Threaded module body
//------------------------------------------------------------------------------

void
core::ThreadModule::threadInitialize()
{
    LOG_INFO("Dummy '%s' module thread initialization.", getName());
}

bool
core::ThreadModule::threadLoopBody()
{
    LOG_INFO("Dummy '%s' module thread loop body.", getName());
    return false;
}

void
core::ThreadModule::threadTerminate()
{
    LOG_INFO("Dummy '%s' module thread termination.", getName());
}

//------------------------------------------------------------------------------
// Utils
//------------------------------------------------------------------------------

core::State
core::ThreadModule::getThreadState() const noexcept
{
    return m_thread_module.getState();
}

const std::vector<core::State>&
core::ThreadModule::getThreadStateHistory() const noexcept
{
    return m_thread_module.getStateHistory();
}

//------------------------------------------------------------------------------

bool
core::ThreadModule::isRunning() const noexcept
{
    return m_is_running;
}

void
core::ThreadModule::threadLoop() noexcept
{
    LOGGER_INIT(getName());

    bool flag = true;
    while (flag)
    {
        if (!KERNEL.isRunning())
        {
            m_thread_module.close();
        }
        flag = m_thread_module.execute();
        util::Yield::small();
    }
    m_is_running = false;
}

//------------------------------------------------------------------------------
