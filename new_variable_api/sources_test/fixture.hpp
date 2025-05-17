#pragma once

#include <gtest/gtest.h>

#include <iostream>
#include <stdio.h>
#include <unordered_map>

namespace kustest
{

class Fixture : public testing::Test
{
public:
    Fixture() noexcept;
    virtual ~Fixture() noexcept;

    virtual void setUp() noexcept;
    virtual void tearDown() noexcept;

    template <typename... Args>
    static void print(Args... args)
    {
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
        std::fflush(stdout);
        std::fflush(stderr);
    }
};

#define ADD_BREAKPOINT Fixture::print(__func__, __LINE__)

} // namespace kustest
