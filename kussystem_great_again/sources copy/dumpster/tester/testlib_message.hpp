#ifndef TESTLIB_MESSAGE_HPP
#define TESTLIB_MESSAGE_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

struct TestLibMessage
{
public:
    int mTestNumber;

    str::String mTest;
    str::String mAnswer;
    str::String mOutput;

    str::String mTestSize;
    str::String mAnswerSize;
    str::String mOutputSize;

    void makeTestSizes() noexcept;
    void makeAnswerSizes() noexcept;
    void makeOutputSizes() noexcept;

private:
    union
    {
        uint8_t message[8];
        uint64_t value;
    } StringSizeCoder{};

    void makeSize(char* aStr, char* aSize) noexcept;
};

//--------------------------------------------------------------------------------

#endif // !TESTLIB_MESSAGE_HPP