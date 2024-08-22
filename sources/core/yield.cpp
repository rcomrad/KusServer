#include "yield.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void
core::Yield::large() noexcept
{
    std::this_thread::sleep_for(1000ms);
}

void
core::Yield::medium() noexcept
{
    std::this_thread::sleep_for(200ms);
}

void
core::Yield::small() noexcept
{
    std::this_thread::sleep_for(10ms);
}
