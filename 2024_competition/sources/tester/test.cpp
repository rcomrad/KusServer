#include "test.hpp"

//--------------------------------------------------------------------------------

#include "domain/log.hpp"

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
    dom::writeInfo("Start_new_test", "Test_cell_num:", mTesterID);

    mTLM = aTestReader.getTest();
    mTLM.makeTestSizes();
    mTLM.makeAnswerSizes();

    checkTest();
    mThreadSignals->push(mTesterID);

    dom::writeInfo("End_test#", mTLM.mTestNumber, "Test_cell_num:", mTesterID);
}

//--------------------------------------------------------------------------------

void
test::Test::checkTest() noexcept
{
    dom::writeInfo("Checking_test#", mTLM.mTestNumber,
                   "Test_cell_num:", mTesterID);

    mSolutionProcess = *mSolutionTemplate;
    mSolutionProcess.create();
    dom::writeInfo("Test_cell_num:", mTesterID, "Write_data:", mTLM.mTest);
    mSolutionProcess.writeData(mTLM.mTest);
    auto testRes = mSolutionProcess.runWithLimits();
    // dom::writeInfo("Test_cell_num:", mTesterID, "Test:", mTLM.mTest);
    if (!testRes.has_value())
    {
        dom::writeInfo("Test_cell_num:", mTesterID, "Output:", mTLM.mOutput);
        mVerdict = TestVerdict::TLE;
    }
    else
    {
        mUsedTime   = testRes.value().timeLimit;
        mUsedMemory = testRes.value().memoryLimit;

        mSolutionProcess.readData(mTLM.mOutput);
        mTLM.makeOutputSizes();

        dom::writeInfo("Test_cell_num:", mTesterID, "Test:", mTLM.mTest);
        dom::writeInfo("Test_cell_num:", mTesterID, "Output:", mTLM.mOutput);
        dom::writeInfo("Test_cell_num:", mTesterID, "Answer:", mTLM.mAnswer);

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
    dom::writeInfo("Test_cell_num:", mTesterID, "Result_evoluation");
    dom::writeInfo("time:", mUsedTime);
    dom::writeInfo("memory:", mUsedMemory);

    std::string temp;

    mCheckerProcess.readData(temp);

    if (temp.empty())
    {
        mVerdict = TestVerdict::TLE;
        dom::writeInfo("Result_is_TLE");
        dom::writeInfo("wanted:", mUsedTime);
        dom::writeInfo("received:", mTimeLimit);
    }
    else if (temp.substr(0, 2) != "ok")
    {
        mVerdict = TestVerdict::WA;
        dom::writeInfo("Result_not_okay");
        dom::writeInfo("Checker_output:", temp);
    }
    else if (mUsedTime > mTimeLimit)
    {
        mVerdict = TestVerdict::TLE;
        dom::writeInfo("Result_is_TLE");
        dom::writeInfo("wanted:", mUsedTime);
        dom::writeInfo("received:", mTimeLimit);
    }
    else if (mUsedMemory > mMemoryLimit)
    {
        mVerdict = TestVerdict::MLE;
        dom::writeInfo("Result_is_MLE");
        dom::writeInfo("wanted:", mUsedMemory);
        dom::writeInfo("received:", mMemoryLimit);
    }
    else
    {
        mVerdict = TestVerdict::OK;
        dom::writeInfo("Test_cell_num:", mTesterID, "ok_test_passed");
    }
}

//--------------------------------------------------------------------------------
