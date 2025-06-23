#pragma once

#include <atomic>
#include <thread>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"
#include "kernel/framework/module/thread_module.hpp"
#include "kernel/tester/commands_fixture.hpp"
#include "kernel/utility/synchronization/condvar.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

#include "definitions.hpp"
#include "module_constructor.hpp"

namespace kustest
{

template <typename TestType>
class SyncTester
{
public:
    SyncTester(CommandsFixture& a_fixture) : m_fixture(a_fixture)
    {
    }

    ~SyncTester()
    {
    }

    void setModuleStates(const std::initializer_list<MState>& a_required_list)
    {
        m_answer = std::vector<MState>(a_required_list);
    }

    virtual void exec()
    {
        util::Condvar has_started;
        auto& module = *ModuleConstructor::create<TestType>(has_started);
        m_fixture.execCommand("mod_add test");
        has_started.wait();
        endTest();
        // wait(0); // 1 or 2
        checkStates(module);
    }

protected:
    CommandsFixture& m_fixture;

    virtual void checkStates(const core::Module& a_module)
    {
        checkImpl(m_answer, a_module.getStateHistory(), a_module.getState(),
                  "sync");
    }

    void checkImpl(const std::vector<MState>& a_answer,
                   const std::vector<MState>& a_result,
                   MState a_final_state,
                   const std::string& a_level)
    {
        EXPECT_EQ(a_result, a_answer) << a_level;
        EXPECT_EQ(a_final_state, a_answer.back()) << a_level;
    }

    virtual void endTest()
    {
        wait(0);
    }

    void wait(int a_count)
    {
        util::Sleep::medium();
        while (std::stoi(m_fixture.execCommand("mod_active_count")) != a_count)
        {
            util::Sleep::yield();
        }
    }

private:
    std::vector<MState> m_answer;
    std::vector<MState> m_results;
};

template <template <typename> typename BaseType,
          typename ChildType,
          size_t ThreadCount = 1>
class ExternalKill : public BaseType<ChildType>
{
    using Base = BaseType<ChildType>;

public:
    using Base::Base;

protected:
    void endTest() final
    {
        Base::wait(ThreadCount);
        Base::m_fixture.terminateKernel();
    }
};

} // namespace kustest
