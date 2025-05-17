#include "tester.hpp"

//--------------------------------------------------------------------------------

#include <boost/date_time.hpp>

#include <cmath>

#include "database/connection_manager.hpp"

#include "file/path.hpp"
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

std::shared_ptr<proc::Process>
checker(const std::string& aFileName) noexcept
{
    std::shared_ptr<proc::Process> result = std::make_shared<proc::Process>();
    result->setComand({aFileName});
    return result;
}

void
test::Tester::run(data::Table<data::Submission>&& aSubmission) noexcept
{
    mIsmIsCorapted = false;

    auto& submission = aSubmission[0];
    data::Table<data::Problem> problemTable;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        problemTable    = connection.val.getData<data::Problem>(
            "id=" + data::wrap(submission.problem_id));
        submission.verdict = "GG";
        connection.val.update(aSubmission);
    }

    auto& problem = problemTable[0];

    std::string curPath = file::Path::getInstance().getPath("problem").value();
    curPath += problem.nickname + "/";

    std::string submissionPath = submission.source_name;
    std::string checkerPath    = problem.checker_name;

    if (checkerPath == "NUN")
    {
        checkerPath = curPath + "checker.cpp";
    }
    else
    {
        checkerPath =
            file::Path::getInstance().getPath("checker").value() + checkerPath;
    }

    auto workDir =
        file::Path::getInstance().getPath("working_directory").value();
    auto solProc = prepareFile(submissionPath, workDir + "sus_solution");
    // auto checkProc = prepareFile(checkerPath, workDir + "sus_checker");
    auto checkProc = checker(checkerPath);

    if (!mIsmIsCorapted)
    {
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
    }
    else
    {
        mFinalVerdict = Test::TestVerdict::CE;
    }

    if (mFinalVerdict != Test::TestVerdict::OK) aSubmission[0].test = ttt - 1;
    submission.verdict = verdictTostring(mFinalVerdict);
    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.update(aSubmission);
    }
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
    START_LOG_BLOCK("Checking_participant_code");
    boost::posix_time::ptime timeLocal =
        boost::posix_time::second_clock::local_time();

    for (int i = 1;;)
    {
        ttt         = i;
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

    WRITE_LOG("Final_time:", mFinalTime);
    END_LOG_BLOCK("Final_memory:", mFinalMemory);
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
    WRITE_LOG("Final_result:", result);
    return result;
}

//--------------------------------------------------------------------------------
