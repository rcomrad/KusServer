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
    TestReader(const char* aTestPath, int aTestCount) noexcept;
    TestLibMessage getTest() noexcept;
    bool hasTest() noexcept;

public:
    int mTestNum;
    int mTestCount;
    str::String mTestPath;
    std::mutex mMutex;
};
} // namespace test

//--------------------------------------------------------------------------------

#endif // !TEST_READER_HPP