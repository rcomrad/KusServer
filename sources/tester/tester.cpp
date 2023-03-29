#include "tester.hpp"

//--------------------------------------------------------------------------------

#include <cmath>

#include "domain/path.hpp"

#include "process/limits.hpp"

#include "compiler.hpp"

//--------------------------------------------------------------------------------

test::Tester::Tester(uint8_t aThreadCount) noexcept
    : mThreadCount(aThreadCount),
      mThreadSignals(aThreadCount),
      mFinalVerdict(Test::TestVerdict::OK),
      mFinalTime(0),
      mFinalMemory(0)
{
}

//--------------------------------------------------------------------------------

void
test::Tester::run(data::Table<data::Submission>&& aSubmission) noexcept
{
    data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
    auto& submission = aSubmission[0];
    auto problemTable =
        dbq.getData<data::Problem>("id=" + data::wrap(submission.problem_id));
    auto& problem = problemTable[0];

    std::string curPath = dom::Path::getPath("problem").value();
    curPath += problem.nickname + "/";

    std::string submissionPath = submission.source_name;
    std::string checkerPath    = problem.checker_name;

    if (checkerPath.empty())
    {
        checkerPath = curPath + "checker.cpp";
    }
    else
    {
        checkerPath = dom::Path::getPath("checker").value() + checkerPath;
    }

    auto workDir   = dom::Path::getPath("working_directory").value();
    auto solProc   = prepareFile(submissionPath, workDir + "sus_solution");
    auto checkProc = prepareFile(checkerPath, workDir + "sus_checker");

    proc::Limits limits;
    limits.timeLimit   = problem.time_limit;
    limits.memoryLimit = problem.memory_limit;
    solProc->setLimits(limits);

    // Test testTemplate(solProc, checkProc, &mThreadSignals);
    // testTemplate.setLimits(limits);
    // mTests.resize(mThreadCount, testTemplate);

    mTests.reserve(mThreadCount);
    for (size_t i = 0; i < mThreadCount; ++i)
    {
        mThreadSignals.push(i);
        // mTests[i].setTesterID(i);
        mTests.emplace_back(solProc, checkProc, &mThreadSignals, i);
        mTests[i].setLimits(limits);
    }

    TestReader testReader(curPath + "test/", problem.test_count);
    check(testReader);
    submission.verdict = verdictTostring(mFinalVerdict);
    dbq.update(aSubmission);
}

//--------------------------------------------------------------------------------

std::shared_ptr<proc::Process>
test::Tester::prepareFile(const std::string& aFileName,
                          const std::string& aOutputFileName) const noexcept
{
    std::shared_ptr<proc::Process> result = std::make_shared<proc::Process>();
    auto cmd = test::Compiler::getExecutableCommand(aFileName, aOutputFileName);
    result->setComand(cmd);
    return result;
}

//--------------------------------------------------------------------------------

void
test::Tester::check(TestReader& aTestReader) noexcept
{
    START_LOG_BLOCK("Checking_participant_code");

    int finished = 0;
    while (finished < mThreadCount)
    {
        auto signal = mThreadSignals.getSignal();
        if (signal.has_value())
        {
            WRITE_LOG("Signal_number", signal.value());
            auto& test = mTests[signal.value()];

            if (mFinalVerdict == Test::TestVerdict::OK)
            {
                mFinalVerdict = test.getVerdict();
            }
            mFinalTime   = std::max(mFinalTime, test.getUsedTime());
            mFinalMemory = std::max(mFinalMemory, test.getUsedMemory());

            if (aTestReader.hasTest() && mFinalVerdict == Test::TestVerdict::OK)
            {
                test.run(aTestReader);
            }
            else
            {
                finished++;
            }
        }
    }

    WRITE_LOG("Final_time:", mFinalTime);
    END_LOG_BLOCK("Final_memory:", mFinalMemory);
}

std::string
test::Tester::verdictTostring(const Test::TestVerdict& aVerdict) const noexcept
{
    std::string result;
    switch (aVerdict)
    {
        case Test::TestVerdict::OK:
            result = "OK";
            break;
        case Test::TestVerdict::WA:
            result = "WA";
            break;
        case Test::TestVerdict::TLE:
            result = "TLE";
            break;
        case Test::TestVerdict::MLE:
            result = "MLE";
            break;
        case Test::TestVerdict::PE:
            result = "WA";
            break;
        case Test::TestVerdict::NUN:
            result = "WA";
            break;
    }
    WRITE_LOG("Final_result:", result);
    return result;
}

//--------------------------------------------------------------------------------
