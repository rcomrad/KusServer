#include "condvar.hpp"

core::Condvar::Condvar() noexcept : m_notify_flag(false)
{
}

void
core::Condvar::wait() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_condvar.wait(lock, [&] { return m_notify_flag; });
}

void
core::Condvar::notify() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_notify_flag = true;
    m_condvar.notify_one();
}
