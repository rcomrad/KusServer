#pragma once

#include <thread>

#include "kernel/framework/module/kernel.hpp"
#include "kernel/utility/synchronization/yield.hpp"

#include "definitions.hpp"
#include "tester_thread.hpp"

namespace kustest
{

class SynchronizationModule : public core::ThreadModule
{
public:
    using core::ThreadModule::ThreadModule;

    bool isActive()
    {
        return getState() >= MState::ALIVE && getThreadState() >= MState::ALIVE;
    }

protected:
    bool threadLoopBody() override
    {
        return true;
    }
};

class SynchronizationSelfClose : public SynchronizationModule
{
    using SynchronizationModule::SynchronizationModule;

protected:
    bool threadLoopBody() override
    {
        return m_loop_cnt++ < 1;
    }

private:
    int m_loop_cnt = 0;
};

//------------------------------------------------------------------------------

template <template <typename> typename TestType>
class ThreadModuleTester : public ThreadTester<TestType<SynchronizationModule>>
{
};

template <template <typename> typename TestType>
class ThreadSelfCloser : public ThreadTester<TestType<SynchronizationSelfClose>>
{
};

template <template <typename> typename TestType>
class ThreadExternalKillTester
    : public ExternalKill<ThreadTester, TestType<SynchronizationModule>>
{
};

} // namespace kustest
