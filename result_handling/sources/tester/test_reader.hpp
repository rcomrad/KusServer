#ifndef TEST_READER_HPP
#define TEST_READER_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <string>

#include "testlib_message.hpp"

//--------------------------------------------------------------------------------

namespace test
{
class TestReader
{
public:
    TestReader(const std::string& aTestPath, int aTestCount) noexcept;
    TestLibMessage getTest() noexcept;
    bool hasTest() noexcept;

public:
    int mTestNum;
    int mTestCount;
    std::string mTestPath;
    std::mutex mMutex;
};
} // namespace test

//--------------------------------------------------------------------------------

#endif // !TEST_READER_HPP