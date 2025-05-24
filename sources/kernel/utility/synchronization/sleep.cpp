#include "sleep.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void
util::Sleep::large() noexcept
{
    std::this_thread::sleep_for(1000ms);
}

void
util::Sleep::medium() noexcept
{
    std::this_thread::sleep_for(200ms);
}

void
util::Sleep::small() noexcept
{
    std::this_thread::sleep_for(10ms);
}

void
util::Sleep::yield() noexcept
{
    std::this_thread::yield();
}
