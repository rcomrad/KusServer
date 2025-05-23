#include "local.hpp"

core::Logger&
core::LocalLogger::getLogger() noexcept
{
    thread_local Logger instance;
    return instance;
}
