#include "synchronized_state.hpp"

#include "kernel/framework/logger/include_me.hpp"

core::SynchronizedState::SynchronizedState()
    : m_base_state(State::CREATED),
      m_thread_state(State::CREATED),
      m_history({core::State::NUN})
{
}

#include <iostream>

bool
core::SynchronizedState::baseTrySitchTo(State a_state) noexcept
{
    bool result = true;
    if (a_state == State::CLOSING)
    {
        result = m_thread_state > State::__FINISHED;
    }
    if (result)
    {
        m_base_state = a_state;
    }
    return result;
}

bool
core::SynchronizedState::threadTrySitchTo(State a_state) noexcept
{
    bool result = true;
    if (a_state == State::CREATED)
    {
        result = m_base_state > State::__WORKING;
    }
    if (result)
    {
        m_thread_state = a_state;
        const std::lock_guard lock(m_history_mutex);
        m_history.emplace_back(a_state);
    }
    return result;
}

bool
core::SynchronizedState::checkThreadValidity() noexcept
{
    return State(m_base_state) < State::__FINISHED;
}

core::State
core::SynchronizedState::getThreadState() const noexcept
{
    return m_thread_state;
}

const std::vector<core::State>&
core::SynchronizedState::getThreadHistory() const noexcept
{
    const std::lock_guard lock(m_history_mutex);
    return m_history;
}
