#include "test.hpp"

//--------------------------------------------------------------------------------

#include "general_tools/log.hpp"

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
    LOG_INFO("Start_new_test", "Test_cell_num:", mTesterID);

    mTLM = aTestReader.getTest();
    mTLM.makeTestSizes();
    mTLM.makeAnswerSizes();

    checkTest();
    mThreadSignals->push(mTesterID);

    LOG_INFO("End_test#", mTLM.mTestNumber, "Test_cell_num:", mTesterID);
}

//--------------------------------------------------------------------------------

void
test::Test::checkTest() noexcept
{
    LOG_INFO("Checking_test#", mTLM.mTestNumber,
                   "Test_cell_num:", mTesterID);

    mSolutionProcess = *mSolutionTemplate;
    mSolutionProcess.create();
    LOG_INFO("Test_cell_num:", mTesterID, "Write_data:", mTLM.mTest);
    // mSolutionProcess.writeData(mTLM.mTest, true);
    auto testRes = mSolutionProcess.runWithLimits();

    if (!testRes.has_value())
    {
        LOG_INFO("Test_cell_num:", mTesterID, "Output:", mTLM.mOutput);
        mVerdict = TestVerdict::TLE;
    }
    else
    {
        mUsedTime   = testRes.value().timeLimit;
        mUsedMemory = testRes.value().memoryLimit;

        mSolutionProcess.readData(mTLM.mOutput);
        mTLM.makeOutputSizes();

        LOG_INFO("Test_cell_num:", mTesterID, "Test:", mTLM.mTest);
        LOG_INFO("Test_cell_num:", mTesterID, "Output:", mTLM.mOutput);
        LOG_INFO("Test_cell_num:", mTesterID, "Answer:", mTLM.mAnswer);

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
    LOG_INFO("Test_cell_num:", mTesterID, "Result_evoluation");
    LOG_INFO("time:", mUsedTime);
    LOG_INFO("memory:", mUsedMemory);

    std::string temp;

    mCheckerProcess.readData(temp);

    if (temp.empty())
    {
        mVerdict = TestVerdict::TLE;
        LOG_INFO("Result_is_TLE");
        LOG_INFO("wanted:", mUsedTime);
        LOG_INFO("received:", mTimeLimit);
    }
    else if (temp.substr(0, 2) != "ok")
    {
        mVerdict = TestVerdict::WA;
        LOG_INFO("Result_not_okay");
        LOG_INFO("Checker_output:", temp);
    }
    else if (mUsedTime > mTimeLimit)
    {
        mVerdict = TestVerdict::TLE;
        LOG_INFO("Result_is_TLE");
        LOG_INFO("wanted:", mUsedTime);
        LOG_INFO("received:", mTimeLimit);
    }
    else if (mUsedMemory > mMemoryLimit)
    {
        mVerdict = TestVerdict::MLE;
        LOG_INFO("Result_is_MLE");
        LOG_INFO("wanted:", mUsedMemory);
        LOG_INFO("received:", mMemoryLimit);
    }
    else
    {
        mVerdict = TestVerdict::OK;
        LOG_INFO("Test_cell_num:", mTesterID, "ok_test_passed");
    }
}

//--------------------------------------------------------------------------------
