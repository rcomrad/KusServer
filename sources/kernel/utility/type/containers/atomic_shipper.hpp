#pragma once

#include <atomic>

namespace utils
{

template <typename Data>
class AtomicShipper
{
public:
    AtomicShipper()
    {
        clearData();
    }

    void store(Data&& a_data)
    {
        if (!hasData())
        {
            m_data = std::move(a_data);
            markData();
        }
    }

    void load(Data& a_data)
    {
        if (hasData())
        {
            a_data = std::move(m_data);
            clearData();
        }
    }

private:
    Data m_data;
    std::atomic_flag m_has_data;

    inline bool hasData() const
    {
        return m_has_data.test(std::memory_order_acquire);
    }

    inline void markData()
    {
        m_has_data.test_and_set(std::memory_order_acq_rel);
    }

    inline void clearData()
    {
        m_has_data.clear(std::memory_order_release);
    }
};

} // namespace utils
