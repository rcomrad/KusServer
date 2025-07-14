#pragma once

#include <cmath>
#include <cstring>
#include <string>
#include <string_view>

namespace util
{

// TODO: static operator() - only in C++23
class PrintSizer
{
public:
    static inline int exec(int a_data)
    {
        return intSize(std::abs(a_data)) + (a_data < 0 ? 1 : 0);
    }

    static inline int exec(const size_t& a_data)
    {
        return intSize(a_data);
    }

    static inline int exec(const double& a_data)
    {
        return std::to_string(a_data).size();
    }

    static inline int exec(const char* a_data)
    {
        return std::strlen(a_data);
    }

    static inline int exec(const std::string& a_data)
    {
        return a_data.size();
    }

    static inline int exec(const std::string_view& a_data)
    {
        return a_data.size();
    }

    static inline int exec(const std::unique_ptr<char[]>& a_data)
    {
        return std::strlen(a_data.get());
    }

private:
    template <typename T>
    static inline int intSize(T a_data)
    {
        a_data  = a_data;
        int cnt = 0;
        while (a_data)
        {
            a_data /= 10;
            cnt++;
        }
        return std::max(cnt, 1);
    }
};

} // namespace util
