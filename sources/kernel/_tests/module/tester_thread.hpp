#pragma once

#include "tester_sync.hpp"

namespace kustest
{

template <typename ChildType>
class ThreadTester : public SyncTester<ChildType>
{
    using Base = SyncTester<ChildType>;

public:
    ThreadTester() = default;

    void setThreadStates(const std::initializer_list<MState>& a_required_list)
    {
        m_answer = std::vector<MState>(a_required_list);
    }

    void exec() override
    {
        Base::exec();
        auto& module = Base::getThreadModule();
        Base::check(m_answer, module.getThreadStateHistory(),
                    module.getThreadState(), "thread");
    }

protected:
    void wait() override
    {
        Base::wait();
        while (Base::getThreadModule().isRunning())
        {
            util::Yield::small();
        }
    }

private:
    std::vector<MState> m_answer;
    std::vector<MState> m_results;
};

} // namespace kustest
