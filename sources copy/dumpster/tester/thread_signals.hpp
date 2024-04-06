#ifndef THREADS_SIGNALS_HPP
#define THREADS_SIGNALS_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <optional>
#include <vector>

//--------------------------------------------------------------------------------

namespace test
{
class ThreadSignals
{
public:
    ThreadSignals(size_t aThreadMaxCount) noexcept;
    ~ThreadSignals() = default;

    ThreadSignals(const ThreadSignals& other)            = delete;
    ThreadSignals& operator=(const ThreadSignals& other) = delete;

    ThreadSignals(ThreadSignals&& other) noexcept            = default;
    ThreadSignals& operator=(ThreadSignals&& other) noexcept = default;

    void push(size_t aSignal) noexcept;
    std::optional<size_t> getSignal() noexcept;

private:
    std::vector<size_t> mSignals;
    mutable std::mutex mSignalMutex;
};
} // namespace test

//--------------------------------------------------------------------------------

#endif // !THREADS_SIGNALS_HPP
