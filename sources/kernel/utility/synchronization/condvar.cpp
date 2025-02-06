#include "condvar.hpp"

util::Condvar::Condvar() noexcept : m_notify_flag(false)
{
}

void
util::Condvar::wait() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_condvar.wait(lock, [&] { return m_notify_flag; });
}

void
util::Condvar::notify() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_notify_flag = true;
    m_condvar.notify_one();
}

// TODO: m_notify_flag is it works for notifyAll?
void
util::Condvar::notifyAll() noexcept
{
    std::unique_lock<std::mutex> lock(m_condvar_mutex);
    m_notify_flag = true;
    m_condvar.notify_all();
}
