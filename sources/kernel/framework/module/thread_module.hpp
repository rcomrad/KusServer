#pragma once

//--------------------------------------------------------------------------------

#include <thread>

#include "module.hpp"
#include "thread_module_interface.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class ThreadModule : public Module
{
public:
    ThreadModule(const std::string& a_name);
    virtual ~ThreadModule();

    virtual void threadInitialize();
    virtual bool threadLoopBody();
    virtual void threadTerminate();

    bool isRunning() const noexcept;

    core::State getThreadState() const noexcept;
    const std::vector<State>& getThreadHistory() const noexcept;

private:
    std::atomic<bool> m_is_running;
    std::thread m_thread;

    ThreadModuleInterface m_thread_module;
    SynchronizedState m_sync_state;

    void threadLoop() noexcept;
    void exec();
};

} // namespace core

//------------------------------------------------------------------------------
