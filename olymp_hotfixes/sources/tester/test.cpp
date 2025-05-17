#include "test.hpp"

//--------------------------------------------------------------------------------

#include "domain/error_message.hpp"

//--------------------------------------------------------------------------------

test::Test::Test(std::shared_ptr<proc::Process> aSolutionTemplate,
                 std::shared_ptr<proc::Process> aCheckerTemplate,
                 ThreadSignals* aThreadSignals,
                 uint8_t aTesterID) noexcept
    : mTesterID(aTesterID),
      mTestNumber(0),
      mSolutionTemplate(aSolutionTemplate),
      mCheckerTemplate(aCheckerTemplate),
      mThreadSignals(aThreadSignals),
      mVerdict(TestVerdict::OK),
      mUsedTime(0),
      mUsedMemory(0),
      mTestThread([]() {})
{
}

//--------------------------------------------------------------------------------

test::Test::~Test()
{
    mTestThread.join();
}

//--------------------------------------------------------------------------------

test::Test::TestVerdict
test::Test::getVerdict() const noexcept
{
    return mVerdict;
}

uint64_t
test::Test::getUsedTime() const noexcept
{
    return mUsedTime;
}

uint64_t
test::Test::getUsedMemory() const noexcept
{
    return mUsedMemory;
}

//--------------------------------------------------------------------------------

void
test::Test::setLimits(const proc::Limits& aTimeMemLimits) noexcept
{
    mTimeLimit   = aTimeMemLimits.timeLimit;
    mMemoryLimit = aTimeMemLimits.memoryLimit;
}

void
test::Test::setTesterID(uint8_t aTesterID) noexcept
{
    mTesterID = aTesterID;
}

//--------------------------------------------------------------------------------

void
test::Test::run(TestReader& aTestReader) noexcept
{
    mTestThread.join();
    mTestThread = std::thread(&Test::runTesting, this, std::ref(aTestReader));
}

//--------------------------------------------------------------------------------

void
test::Test::runTesting(TestReader& aTestReader) noexcept
{
    START_LOG_BLOCK("Start_new_test", "Test_cell_num:", mTesterID);

    mTLM = aTestReader.getTest();
    mTLM.makeTestSizes();
    mTLM.makeAnswerSizes();

    checkTest();
    mThreadSignals->push(mTesterID);

    END_LOG_BLOCK("End_test#", mTLM.mTestNumber, "Test_cell_num:", mTesterID);
}

//--------------------------------------------------------------------------------

void
test::Test::checkTest() noexcept
{
    START_LOG_BLOCK("Checking_test#", mTLM.mTestNumber,
                    "Test_cell_num:", mTesterID);

    mSolutionProcess = *mSolutionTemplate;
    mSolutionProcess.create();
    WRITE_LOG("Test_cell_num:", mTesterID, "Write_data:", mTLM.mTest);
    mSolutionProcess.writeData(mTLM.mTest);
    mSolutionProcess.writeData("\n");
    auto testRes = mSolutionProcess.runWithLimits();

    if (!testRes.has_value())
    {
        WRITE_LOG("Test_cell_num:", mTesterID, "Output:", mTLM.mOutput);
        mVerdict = TestVerdict::TLE;
    }
    else
    {
        mUsedTime   = testRes.value().timeLimit;
        mUsedMemory = testRes.value().memoryLimit;

        mSolutionProcess.readData(mTLM.mOutput);
        mTLM.makeOutputSizes();

        START_LOG_BLOCK("Test_cell_num:", mTesterID, "Test:", mTLM.mTest);
        WRITE_LOG("Test_cell_num:", mTesterID, "Output:", mTLM.mOutput);
        END_LOG_BLOCK("Test_cell_num:", mTesterID, "Answer:", mTLM.mAnswer);
        END_LOG_BLOCK();

        mCheckerProcess = *mCheckerTemplate;
        mCheckerProcess.create();
        mCheckerProcess.writeData(mTLM.mTestSize);
        mCheckerProcess.writeData(mTLM.mTest);

        mCheckerProcess.writeData(mTLM.mOutputSize);
        mCheckerProcess.writeData(mTLM.mOutput);

        mCheckerProcess.writeData(mTLM.mAnswerSize);
        mCheckerProcess.writeData(mTLM.mAnswer);

        if (mCheckerProcess.run()) resultEvoluation();
        else mVerdict = TestVerdict::NUN;
    }
}

//--------------------------------------------------------------------------------

void
test::Test::resultEvoluation() noexcept
{
    START_LOG_BLOCK("Test_cell_num:", mTesterID, "Result_evoluation");
    WRITE_LOG("time:", mUsedTime);
    WRITE_LOG("memory:", mUsedMemory);

    std::string temp;

    mCheckerProcess.readData(temp);

    if (temp.empty())
    {
        mVerdict = TestVerdict::TLE;
        START_LOG_BLOCK("Result_is_TLE");
        WRITE_LOG("wanted:", mUsedTime);
        END_LOG_BLOCK("received:", mTimeLimit);
    }
    else if (temp.substr(0, 2) != "ok")
    {
        mVerdict = TestVerdict::WA;
        START_LOG_BLOCK("Result_not_okay");
        END_LOG_BLOCK("Checker_output:", temp);
    }
    else if (mUsedTime > mTimeLimit)
    {
        mVerdict = TestVerdict::TLE;
        START_LOG_BLOCK("Result_is_TLE");
        WRITE_LOG("wanted:", mUsedTime);
        END_LOG_BLOCK("received:", mTimeLimit);
    }
    else if (mUsedMemory > mMemoryLimit)
    {
        mVerdict = TestVerdict::MLE;
        START_LOG_BLOCK("Result_is_MLE");
        WRITE_LOG("wanted:", mUsedMemory);
        END_LOG_BLOCK("received:", mMemoryLimit);
    }
    else
    {
        mVerdict = TestVerdict::OK;
        START_LOG_BLOCK("Test_cell_num:", mTesterID, "ok_test_passed");
        END_LOG_BLOCK();
    }

    END_LOG_BLOCK();
}

//--------------------------------------------------------------------------------
