#pragma once

#include <atomic>
#include <mutex>
#include <vector>

#include "state.hpp"

namespace core
{

class SynchronizedState
{
public:
    SynchronizedState();

    bool baseTrySitchTo(State a_state) noexcept;
    bool threadTrySitchTo(State a_state) noexcept;
    bool checkThreadValidity() noexcept;

    State getThreadState() const noexcept;
    const std::vector<State>& getThreadHistory() const noexcept;

private:
    std::atomic<State> m_base_state;
    std::atomic<State> m_thread_state;

    mutable std::mutex m_history_mutex;
    std::vector<State> m_history;
};

} // namespace core
