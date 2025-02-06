#pragma once

#include <string>
#include <string_view>

namespace core
{

class LoggingFunctors
{
public:
    static inline int& convert(int& a_data)
    {
        return a_data;
    }

    static inline const int& convert(const int& a_data)
    {
        return a_data;
    }

    static inline size_t& convert(size_t& a_data)
    {
        return a_data;
    }

    static inline const size_t& convert(const size_t& a_data)
    {
        return a_data;
    }

    static inline double& convert(double& a_data)
    {
        return a_data;
    }

    static inline const double& convert(const double& a_data)
    {
        return a_data;
    }

    static inline char* convert(char* a_data)
    {
        return a_data;
    }

    static inline const char* convert(const char* a_data)
    {
        return a_data;
    }

    static inline const char* convert(const std::string& a_data)
    {
        return a_data.c_str();
    }

    static inline const char* convert(const std::string_view& a_data)
    {
        return a_data.data();
    }
};

} // namespace core
