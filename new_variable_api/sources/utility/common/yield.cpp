#include "yield.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void
util::Yield::large() noexcept
{
    std::this_thread::sleep_for(1000ms);
}

void
util::Yield::medium() noexcept
{
    std::this_thread::sleep_for(200ms);
}

void
util::Yield::small() noexcept
{
    std::this_thread::sleep_for(10ms);
}
