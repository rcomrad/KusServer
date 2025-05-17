#pragma once

#include <condition_variable>

namespace core
{

class Condvar
{
public:
    Condvar() noexcept;
    void wait() noexcept;
    void notify() noexcept;

private:
    bool m_notify_flag;
    std::mutex m_condvar_mutex;
    std::condition_variable m_condvar;
};

} // namespace core
