#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <memory>
#include <string>
#include <vector>

#include "kernel/utility/synchronization/condvar.hpp"
#include "kernel/utility/type/lifecycle_manager.hpp"

#include "synchronized_state.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class Module
{
public:
    Module(const std::string& a_name);
    virtual ~Module() = default;

    bool execute() noexcept;

    State getState() const noexcept;
    const std::vector<State>& getStateHistory() const noexcept;
    const std::string& getName() const noexcept;

    void close() noexcept;

    void useBaseSyncState(SynchronizedState* a_sync_state_ptr) noexcept;
    void useThreadSyncState(SynchronizedState* a_sync_state_ptr) noexcept;

protected:
    virtual void initialize();
    virtual bool loopBody();
    virtual void terminate();

private:
    std::string m_name;
    State m_state;
    std::vector<State> m_state_history;

    bool m_base_or_thread;
    SynchronizedState* m_sync_state;

    void changeState(State a_new_state) noexcept;
};

} // namespace core

//------------------------------------------------------------------------------
