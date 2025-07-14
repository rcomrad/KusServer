#pragma once

#include <cstring>
#include <string>
#include <string_view>

namespace util
{

// TODO: static operator() - only in C++23
class PrintEmpty
{
public:
    static inline bool exec(int a_data)
    {
        return a_data == 0;
    }

    static inline bool exec(const size_t& a_data)
    {
        return a_data == 0;
    }

    static inline bool exec(const double& a_data)
    {
        return a_data == 0;
    }

    static inline bool exec(const char* a_data)
    {
        return strlen(a_data) == 0;
    }

    static inline bool exec(const std::string& a_data)
    {
        return a_data.empty();
    }

    static inline bool exec(const std::string_view& a_data)
    {
        return a_data.empty();
    }

    static inline bool exec(const std::unique_ptr<char[]>& a_data)
    {
        return strlen(a_data.get()) == 0;
    }
};

} // namespace util
