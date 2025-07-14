#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <thread>

#include "kernel/utility/synchronization/condvar.hpp"

#include "input_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class InputSTDIN
{
public:
    InputSTDIN();
    ~InputSTDIN();

private:
    std::atomic<bool> m_is_running;

    InputBuffer m_buffer;
    std::thread m_read_thread;
    util::Condvar m_thread_finished;

    void readLoop();
};

} // namespace core

//--------------------------------------------------------------------------------
