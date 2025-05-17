#include "tester.hpp"

//--------------------------------------------------------------------------------

#include <boost/date_time.hpp>

#include <cmath>

#include "database/connection_manager.hpp"

#include "file_data/path.hpp"
#include "process/limits.hpp"

#include "compiler.hpp"
int ttt = 0;
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
#include <cstdio>
void
test::Tester::run(data::Submission&& aSubmission) noexcept
{
    mIsmIsCorapted = false;

    data::Problem problem;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        problem         = connection.val.getData<data::Problem>(
            "id=" + data::wrap(aSubmission.problemID));
    }

    std::string curPath = file::Path::getPathUnsafe("problem");
    curPath += problem.nickname + "/";

    std::string submissionPath = aSubmission.sourceName;
    std::string checkerPath    = problem.checkerName;

    if (checkerPath == "NUN")
    {
        checkerPath = curPath + "checker.cpp";
    }
    else
    {
        checkerPath = file::Path::getPathUnsafe("checker") + checkerPath;
    }

    auto workDir   = file::Path::getPathUnsafe("working_directory");
    auto solProc   = prepareFile(submissionPath, workDir + "sus_solution");
    auto checkProc = prepareFile(checkerPath, workDir + "sus_checker");

    if (!mIsmIsCorapted)
    {
        proc::Limits limits;
        limits.timeLimit   = problem.timeLimit;
        limits.memoryLimit = problem.memoryLimit;
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

        TestReader testReader(curPath + "test/", problem.testCount);
        check(testReader);
    }
    else
    {
        mFinalVerdict = Test::TestVerdict::CE;
    }

    if (mFinalVerdict != Test::TestVerdict::OK) aSubmission.test = ttt;
    if (aSubmission.test < 1) aSubmission.test = 1;
    aSubmission.verdict = verdictTostring(mFinalVerdict);
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.write(aSubmission);
    }

    std::remove("/home/rcomrad/data/working_directory/sus_solution.exe");
}

//--------------------------------------------------------------------------------

std::shared_ptr<proc::Process>
test::Tester::prepareFile(const std::string& aFileName,
                          const std::string& aOutputFileName) const noexcept
{
    std::shared_ptr<proc::Process> result = std::make_shared<proc::Process>();
    auto cmd = test::Compiler::getExecutableCommand(aFileName, aOutputFileName);
    mIsmIsCorapted |= cmd.empty();
    result->setComand(cmd);
    return result;
}

//--------------------------------------------------------------------------------

void
test::Tester::check(TestReader& aTestReader) noexcept
{
    dom::writeInfo("Checking_participant_code");
    boost::posix_time::ptime timeLocal =
        boost::posix_time::second_clock::local_time();

    for (int i = 1;;)
    {
        ttt         = i;
        auto signal = mThreadSignals.getSignal();
        if (signal.has_value())
        {
            dom::writeInfo("Signal_number", signal.value());
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
                timeLocal = boost::posix_time::second_clock::local_time();
            }
            else
            {
                break;
            }

            ++i;
        }

        boost::posix_time::ptime timeLocal2 =
            boost::posix_time::second_clock::local_time();
        auto dur = timeLocal2 - timeLocal;
        if (dur.seconds() > 6)
        {
            mFinalVerdict = Test::TestVerdict::TLE;
            break;
        }
    }

    dom::writeInfo("Final_time:", mFinalTime);
    dom::writeInfo("Final_memory:", mFinalMemory);
}

std::string
test::Tester::verdictTostring(const Test::TestVerdict& aVerdict) const noexcept
{
    std::string result = "ERR";
    switch (aVerdict)
    {
        case Test::TestVerdict::NUN:
            result = "ERR";
            break;
        case Test::TestVerdict::OK:
            result = "OK";
            break;
        case Test::TestVerdict::CE:
            result = "CE";
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
    }
    dom::writeInfo("Final_result:", result);
    return result;
}

//--------------------------------------------------------------------------------
