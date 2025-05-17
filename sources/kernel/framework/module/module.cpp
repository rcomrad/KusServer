#include "module.hpp"

#include "kernel/framework/logger/include_me.hpp"
#include "kernel/framework/module/kernel.hpp"

#include "module_func_try_block.hpp"

//------------------------------------------------------------------------------

core::Module::Module(const std::string& a_name)
    : m_name(a_name), m_sync_state(nullptr), m_base_or_thread(true)
{
    changeState(State::NUN);
}

//------------------------------------------------------------------------------
// Module body
//------------------------------------------------------------------------------

void
core::Module::initialize()
{
    LOG_INFO("Dummy '%s' Module initialization.", m_name);
}

bool
core::Module::loopBody()
{
    LOG_INFO("Dummy '%s' Module loop body.", m_name);
    return false;
}

void
core::Module::terminate()
{
    LOG_INFO("Dummy '%s' Module termination.", m_name);
}

//------------------------------------------------------------------------------
// Utils
//------------------------------------------------------------------------------

core::State
core::Module::getState() const noexcept
{
    return m_state;
}

const std::vector<core::State>&
core::Module::getStateHistory() const noexcept
{
    return m_state_history;
}

const std::string&
core::Module::getName() const noexcept
{
    return m_name;
}

void
core::Module::useBaseSyncState(SynchronizedState* a_sync_state_ptr) noexcept
{
    m_base_or_thread = true;
    m_sync_state     = a_sync_state_ptr;
}

void
core::Module::useThreadSyncState(SynchronizedState* a_sync_state_ptr) noexcept
{
    m_base_or_thread = false;
    m_sync_state     = a_sync_state_ptr;
}

void
core::Module::close() noexcept
{
    switch (m_state)
    {
        case State::NUN:
        case State::RECONSTRUCTION:
        case State::CREATED:
            changeState(State::IDLE);
            break;

        case State::INITIALIZED:
        case State::ALIVE:
        case State::ALIVE_WITH_EXCEPTIONS:
            changeState(State::CLOSING);
            break;

        case State::CLOSING:
        case State::TERMINATED:
        case State::KILLED:
        case State::IDLE:
        case State::SINGLETON_ERROR:
            break;

        default:
            changeState(State::KILLED);
            LOG_ERROR("Undefined module state");
            break;
    }
}

void
core::Module::changeState(State a_new_state) noexcept
{
    if (m_sync_state)
    {
        if (m_base_or_thread ? !m_sync_state->baseTrySitchTo(a_new_state)
                             : !m_sync_state->threadTrySitchTo(a_new_state))
        {
            return;
        }
    }

    m_state = a_new_state;
    m_state_history.emplace_back(m_state);
}

//------------------------------------------------------------------------------
// Body interface
//------------------------------------------------------------------------------

bool
core::Module::execute() noexcept
{
    State new_state = State::NUN;

    if (m_sync_state && !m_base_or_thread &&
        !m_sync_state->checkThreadValidity())
    {
        close();
    }

    switch (m_state)
    {
        case State::NUN:
            new_state = State::CREATED;
            break;
        case State::RECONSTRUCTION:
        case State::CREATED:
            new_state = State::INITIALIZED;
            TRY_BLOCK(initialize(), "initialization",
                      new_state = State::KILLED);
            break;

        case State::INITIALIZED:
            new_state = State::ALIVE;
        case State::ALIVE:
        case State::ALIVE_WITH_EXCEPTIONS:
            TRY_BLOCK(new_state = loopBody() ? new_state : State::CLOSING,
                      "loop", new_state = State::ALIVE_WITH_EXCEPTIONS);
            break;

        case State::CLOSING:
            new_state = State::TERMINATED;
            TRY_BLOCK(terminate(), "termination", new_state = State::KILLED);
            break;
        case State::TERMINATED:
        case State::KILLED:
        case State::IDLE:
        case State::SINGLETON_ERROR:
            return false;
            break;

        default:
            new_state = State::KILLED;
            LOG_ERROR("Undefined module state");
            break;
    }

    if (new_state != State::NUN)
    {
        changeState(new_state);
    }

    return true;
}

//------------------------------------------------------------------------------
