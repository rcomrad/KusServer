#pragma once

#include <string>
#include <string_view>

namespace util
{

// TODO: static operator() - only in C++23
class PrintCaster
{
public:
    static inline int exec(int a_data)
    {
        return a_data;
    }

    static inline const size_t& exec(const size_t& a_data)
    {
        return a_data;
    }

    static inline const double& exec(const double& a_data)
    {
        return a_data;
    }

    static inline const char* exec(const char* a_data)
    {
        return a_data;
    }

    static inline const char* exec(const std::string& a_data)
    {
        return a_data.c_str();
    }

    static inline const char* exec(const std::string_view& a_data)
    {
        return a_data.data();
    }

    static inline const char* exec(const std::unique_ptr<char[]>& a_data)
    {
        return a_data.get();
    }
};

} // namespace util
