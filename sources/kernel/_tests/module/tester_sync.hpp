#pragma once

#include <thread>

#include "kernel/framework/module/kernel.hpp"
#include "kernel/framework/module/thread_module.hpp"
#include "kernel/utility/synchronization/yield.hpp"

#include "definitions.hpp"

namespace kustest
{

template <typename TestType>
class SyncTester
{
public:
    SyncTester() = default;

    void setModuleStates(const std::initializer_list<MState>& a_required_list)
    {
        m_answer = std::vector<MState>(a_required_list);
    }

    virtual void exec()
    {
        core::ModuleRegister<TestType> reg;
        auto& module = getModule();
        m_module     = &module;
        KERNEL.reloadModules();

        wait();
        check(m_answer, module.getStateHistory(), module.getState(), "module");
    }

protected:
    virtual void runKernel()
    {
        KERNEL.runWhileDoesSmth();
    }

    virtual void wait()
    {
        runKernel();
    }

    bool moduleIsActive()
    {
        return m_module->isActive();
    }

    void check(const std::vector<MState>& a_answer,
               const std::vector<MState>& a_result,
               MState a_final_state,
               const std::string& a_name)
    {
        EXPECT_EQ(a_result, a_answer) << a_name;
        EXPECT_EQ(a_final_state, a_answer.back()) << a_name;
    }

    core::ThreadModule& getThreadModule() const noexcept
    {
        return *dynamic_cast<core::ThreadModule*>(m_module);
    }

private:
    TestType* m_module;
    std::vector<MState> m_answer;
    std::vector<MState> m_results;

    TestType& getModule()
    {
        TestType* module_ptr =
            dynamic_cast<TestType*>(global_modules.begin()->get());
        return *module_ptr;
    }
};

template <template <typename> typename BaseType, typename ChildType>
class ExternalKill : public BaseType<ChildType>
{
    using Base = BaseType<ChildType>;

public:
    using Base::Base;

protected:
    void runKernel() override
    {
        std::thread kernel_run([]() { KERNEL.run(); });
        while (!Base::moduleIsActive())
        {
            util::Yield::small();
        }
        KERNEL.stop();
        kernel_run.join();
    }
};

} // namespace kustest
