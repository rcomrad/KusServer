#pragma once

//--------------------------------------------------------------------------------

#include <thread>

#include "input_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class InputSTDIN
{
public:
    HOLY_TRINITY_SINGLETON(InputSTDIN);
    
    // SINGL_VOID_METHOD(listen, ());
    // SINGL_VOID_METHOD(unlisten, ());

private:
    InputSTDIN() noexcept;

    InputBuffer m_buffer;
    std::thread m_read_thread;

    void readLoop() noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
