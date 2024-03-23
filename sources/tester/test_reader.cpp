#include "test_reader.hpp"

//--------------------------------------------------------------------------------

#include "file_data/file.hpp"

//--------------------------------------------------------------------------------

test::TestReader::TestReader(const std::string& aTestPath,
                             int aTestCount) noexcept
    : mTestNum(1), mTestCount(aTestCount), mTestPath(aTestPath)
{
}

//--------------------------------------------------------------------------------

TestLibMessage
test::TestReader::getTest() noexcept
{
    TestLibMessage result;
    mMutex.lock();
    std::string sn = std::to_string(mTestNum);
    if (sn.size() < 2) sn = "0" + sn;
    result.mTest = file::File::getAllData(mTestPath + sn + "");
    result.mTest.push_back('\n');
    result.mAnswer     = file::File::getAllData(mTestPath + sn + ".a");
    result.mTestNumber = mTestNum;
    mTestNum++;
    mMutex.unlock();
    return result;
}

//--------------------------------------------------------------------------------

bool
test::TestReader::hasTest() noexcept
{
    const std::lock_guard<std::mutex> lock(mMutex);
    return mTestNum <= mTestCount;
}

//--------------------------------------------------------------------------------
