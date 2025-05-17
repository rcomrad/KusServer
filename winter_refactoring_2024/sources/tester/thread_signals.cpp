#include "thread_signals.hpp"

//--------------------------------------------------------------------------------

#include "general_tools/log.hpp"

//--------------------------------------------------------------------------------

test::ThreadSignals::ThreadSignals(size_t aThreadMaxCount) noexcept
{
    mSignals.reserve(aThreadMaxCount);
}

//--------------------------------------------------------------------------------

void
test::ThreadSignals::push(size_t aSignal) noexcept
{
    mSignalMutex.lock();
    mSignals.emplace_back(aSignal);
    mSignalMutex.unlock();
}

//--------------------------------------------------------------------------------

std::optional<size_t>
test::ThreadSignals::getSignal() noexcept
{
    // WRITE_LOG("Signals_count", mSignals.size());
    std::optional<size_t> result;
    mSignalMutex.lock();
    if (mSignals.size())
    {
        result = mSignals.back();
        mSignals.pop_back();
        // WRITE_LOG("Signal_returned", result.value());
    }
    mSignalMutex.unlock();

    // if (result.has_value()) WRITE_LOG("Signal_returned", result.value());
    return result;
}

//--------------------------------------------------------------------------------
