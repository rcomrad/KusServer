#include "base_process.hpp"

//--------------------------------------------------------------------------------

proc::BaseProcess::BaseProcess() noexcept
    : mTimeLimit(MAX_TIME_LIMIT), mMemoryLimit(MAX_MEMORY_LIMIT)
{
}

//--------------------------------------------------------------------------------

void
proc::BaseProcess::setLimits(const proc::Limits& aTimeMemLimits) noexcept
{
    mTimeLimit   = aTimeMemLimits.timeLimit;
    mMemoryLimit = aTimeMemLimits.memoryLimit;

    if (mTimeLimit > MAX_TIME_LIMIT)
    {
        mTimeLimit = MAX_TIME_LIMIT;
    }
    if (mMemoryLimit > MAX_MEMORY_LIMIT)
    {
        mMemoryLimit = MAX_MEMORY_LIMIT;
    }
}

//--------------------------------------------------------------------------------
