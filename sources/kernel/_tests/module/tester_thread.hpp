#pragma once

#include "tester_sync.hpp"

namespace kustest
{

template <typename ChildType>
class ThreadTester : public SyncTester<ChildType>
{
    using Base = SyncTester<ChildType>;
    using Base::Base;

public:
    ThreadTester() = default;

    void setThreadStates(const std::initializer_list<MState>& a_required_list)
    {
        m_answer = std::vector<MState>(a_required_list);
    }

    void checkStates(const core::Module& a_module) final
    {
        Base::checkStates(a_module);

        const auto& thread_module =
            dynamic_cast<const core::ThreadModule&>(a_module);
        Base::checkImpl(m_answer, thread_module.getThreadHistory(),
                        thread_module.getThreadState(), "thread");
    }

private:
    std::vector<MState> m_answer;
};

} // namespace kustest
