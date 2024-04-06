#ifndef TEST_HPP
#define TEST_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <memory>
#include <thread>

#include "process/limits.hpp"
#include "process/process.hpp"

#include "test_reader.hpp"
#include "testlib_message.hpp"
#include "thread_signals.hpp"

//--------------------------------------------------------------------------------

namespace test
{
class Test
{
public:
    enum class TestVerdict
    {
        NUN,
        OK,
        CE,
        WA,
        TLE,
        MLE,
        PE
    };

    Test(std::shared_ptr<proc::Process> aSolutionTemplate,
         std::shared_ptr<proc::Process> aCheckerTemplate,
         ThreadSignals* aThreadSignals,
         uint8_t aTesterID = 0) noexcept;
    ~Test();

    Test(const Test& other) noexcept            = default;
    Test& operator=(const Test& other) noexcept = default;

    Test(Test&& other) noexcept            = default;
    Test& operator=(Test&& other) noexcept = default;

    bool isFinished() const noexcept;

    TestVerdict getVerdict() const noexcept;
    uint64_t getUsedTime() const noexcept;
    uint64_t getUsedMemory() const noexcept;

    void setLimits(const proc::Limits& aTimeMemLimits) noexcept;
    void setTesterID(uint8_t aTesterID) noexcept;

    void run(TestReader& aTestReader) noexcept;

private:
    proc::Process mSolutionProcess;
    proc::Process mCheckerProcess;
    std::shared_ptr<proc::Process> mSolutionTemplate;
    std::shared_ptr<proc::Process> mCheckerTemplate;

    test::ThreadSignals* mThreadSignals;
    std::thread mTestThread;
    TestLibMessage mTLM;

    uint16_t mTestNumber;
    uint8_t mTesterID;

    TestVerdict mVerdict;
    uint64_t mUsedTime;
    uint64_t mUsedMemory;
    uint64_t mTimeLimit;
    uint64_t mMemoryLimit;

    void runTesting(TestReader& aTestReader) noexcept;

    void checkTest() noexcept;
    void resultEvoluation() noexcept;
};
} // namespace test

//--------------------------------------------------------------------------------

#endif // !TEST_HPP