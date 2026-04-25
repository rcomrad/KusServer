#pragma once

#include <condition_variable>

namespace utils
{

class Condvar
{
public:
    Condvar() noexcept;
    void wait() noexcept;
    void notify() noexcept;
    void notifyAll() noexcept;

private:
    bool m_notify_flag;
    std::mutex m_condvar_mutex;
    std::condition_variable m_condvar;
};

} // namespace utils
