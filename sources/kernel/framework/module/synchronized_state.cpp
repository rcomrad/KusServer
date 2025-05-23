#include "synchronized_state.hpp"

#include "kernel/framework/logger/include_me.hpp"

core::SynchronizedState::SynchronizedState()
    : m_base_state(State::CREATED), m_thread_state(State::CREATED)
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
    // std::cout << std::format("Base: {} {}\n", int(a_state), result);
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
    }
    // std::cout << std::format("Child: {} {}\n", int(a_state), result);
    return result;
}

bool
core::SynchronizedState::checkThreadValidity() noexcept
{
    // std::cout << std::format("Validity: {}\n", State(m_base_state) <
    // State::__FINISHED);
    return State(m_base_state) < State::__FINISHED;
}
