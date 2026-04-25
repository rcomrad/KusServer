#include "condvar.hpp"

utils::Condvar::Condvar() noexcept : m_notify_flag(false)
{
}

void
utils::Condvar::wait() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_condvar.wait(lock, [&] { return m_notify_flag; });
}

void
utils::Condvar::notify() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_notify_flag = true;
    m_condvar.notify_one();
}

// TODO: m_notify_flag is it works for notifyAll?
void
utils::Condvar::notifyAll() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_notify_flag = true;
    m_condvar.notify_all();
}
