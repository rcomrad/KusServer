#ifndef TESTLIB_MESSAGE_HPP
#define TESTLIB_MESSAGE_HPP

//--------------------------------------------------------------------------------

#include <cstdint>
#include <string>

//--------------------------------------------------------------------------------

struct TestLibMessage
{
public:
    int mTestNumber;

    std::string mTest;
    std::string mAnswer;
    std::string mOutput;

    std::string mTestSize;
    std::string mAnswerSize;
    std::string mOutputSize;

    void makeTestSizes() noexcept;
    void makeAnswerSizes() noexcept;
    void makeOutputSizes() noexcept;

private:
    union
    {
        uint8_t message[8];
        uint64_t value;
    } StringSizeCoder{};

    void makeSize(std::string& aStr, std::string& aSize) noexcept;
};

//--------------------------------------------------------------------------------

#endif // !TESTLIB_MESSAGE_HPP
