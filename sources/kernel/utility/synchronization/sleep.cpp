#include "sleep.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void
utils::Sleep::large() noexcept
{
    std::this_thread::sleep_for(1000ms);
}

void
utils::Sleep::medium() noexcept
{
    std::this_thread::sleep_for(200ms);
}

void
utils::Sleep::small() noexcept
{
    std::this_thread::sleep_for(10ms);
}

void
utils::Sleep::yield() noexcept
{
    std::this_thread::yield();
}
