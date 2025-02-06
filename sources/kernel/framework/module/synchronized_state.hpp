#pragma once

#include <atomic>

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

private:
    std::atomic<State> m_base_state;
    std::atomic<State> m_thread_state;
};

} // namespace core
