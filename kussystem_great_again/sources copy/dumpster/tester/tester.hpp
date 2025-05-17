#ifndef TESTER_HPP
#define TESTER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "database/database_structures.hpp"

#include "process/process.hpp"

#include "test.hpp"
#include "test_reader.hpp"
#include "thread_signals.hpp"

//--------------------------------------------------------------------------------

namespace test
{
class Tester
{
public:
    Tester(uint8_t aThreadCount) noexcept;
    ~Tester() = default;

    Tester(const Tester& other) noexcept            = default;
    Tester& operator=(const Tester& other) noexcept = default;

    Tester(Tester&& other) noexcept            = default;
    Tester& operator=(Tester&& other) noexcept = default;

    void run(data::Submission&& aSubmission) noexcept;

    std::shared_ptr<proc::Process> prepareFile(
        const char* aFileName,
        const char* aOutputFileName) const noexcept;

    void check(TestReader& aTestReader) noexcept;

    str::String verdictTostring(
        const Test::TestVerdict& aVerdict) const noexcept;

private:
    uint8_t mThreadCount;
    test::ThreadSignals mThreadSignals;
    std::vector<Test> mTests;

    Test::TestVerdict mFinalVerdict;
    uint64_t mFinalTime;
    uint64_t mFinalMemory;

    mutable bool mIsmIsCorapted;
};
} // namespace test

//--------------------------------------------------------------------------------

#endif // !TESTER_HPP
