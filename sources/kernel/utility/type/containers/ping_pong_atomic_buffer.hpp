#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"

#include <atomic>
#include <vector>

namespace utils
{

template <typename Data>
class PingPongAtomicBuffer
{
public:
    PingPongAtomicBuffer()
    {
        m_is_second_ready_to_write.clear();
    }

    PingPongAtomicBuffer(PingPongAtomicBuffer&& a_other)
    {
        m_first  = std::move(a_other.m_first);
        m_second = std::move(a_other.m_second);

        if (a_other.m_is_second_ready_to_write.test())
        {
            m_is_second_ready_to_write.test_and_set();
        }
        else
        {
            m_is_second_ready_to_write.clear();
        }
    }

    void acquireRead(std::vector<Data>&& a_container)
    {
        if (!m_is_second_ready_to_write.test(std::memory_order_acquire))
        {
            m_second    = std::move(a_container);
            a_container = std::move(m_first);
            m_is_second_ready_to_write.test_and_set(std::memory_order_acq_rel);
        }
    }

    void acquireWrite(std::vector<Data>&& a_container)
    {
        // uint8_t temp = m_state.load(std::memory_order_acquire);
        if (m_is_second_ready_to_write.test(std::memory_order_acquire))
        {
            m_first     = std::move(a_container);
            a_container = std::move(m_second);
            m_is_second_ready_to_write.clear(std::memory_order_release);
        }
    }

private:
    std::vector<Data> m_first;
    std::vector<Data> m_second;
    std::atomic_flag m_is_second_ready_to_write;
};

} // namespace utils
