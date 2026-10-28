#pragma once

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

// #include <iostream>
// #include <stdio.h>
// #include <unordered_map>

namespace kustest
{

class Fixture : public testing::Test
{
protected:
    Fixture();
    ~Fixture();

    template <typename T>
    T constructWithGarbage()
    {
        T result;
        fillWithGarbage(result);
        return result;
    }

    template <typename T>
    void fillWithGarbage(T& obj)
    {
        auto* bytes = reinterpret_cast<unsigned char*>(&obj);

        for (std::size_t i = 0; i < sizeof(T); ++i, ++m_filler_cnt)
        {
            m_filler_cnt %= 'Z' - 'A' + 1;
            bytes[i] = static_cast<unsigned char>('A' + m_filler_cnt);
        }
    }

private:
    static inline int m_filler_cnt = 0;

    // template <typename... Args>
    // static void print(Args... args)
    // {
    //     ((std::cout << args << " "), ...);
    //     std::cout << std::endl;
    //     std::fflush(stdout);
    //     std::fflush(stderr);
    // }
};

// #define ADD_BREAKPOINT Fixture::print(__func__, __LINE__)

} // namespace kustest
