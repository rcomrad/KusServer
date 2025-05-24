#pragma once

#include "kernel/framework/core/kernel.hpp"

#include "tester_thread.hpp"

namespace kustest
{

class SynchronizationModule : public core::ThreadModule
{
    using Base = core::ThreadModule;
    using Base::Base;

protected:
    bool threadLoopBody() override
    {
        return true;
    }
};

class SynchronizationSelfClose : public SynchronizationModule
{
    using Base = SynchronizationModule;
    using Base::Base;

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
    using Base = ThreadTester<TestType<SynchronizationModule>>;
    using Base::Base;
};

template <template <typename> typename TestType>
class ThreadSelfCloser : public ThreadTester<TestType<SynchronizationSelfClose>>
{
    using Base = ThreadTester<TestType<SynchronizationSelfClose>>;
    using Base::Base;
};

template <template <typename> typename TestType>
class ThreadExternalKillTester
    : public ExternalKill<ThreadTester, TestType<SynchronizationModule>, 2>
{
    using Base = ExternalKill<ThreadTester, TestType<SynchronizationModule>, 2>;
    using Base::Base;
};

} // namespace kustest
