#pragma once

#include <string>
#include <string_view>

namespace util
{

// TODO: static operator() - only in C++23
class PrintSpecifier
{
public:
    static inline auto exec(int)
    {
        return "d";
    }

    static inline auto exec(const size_t&)
    {
        return "zu";
    }

    static inline auto exec(const double&)
    {
        return "f"; // equivalent lf, https://stackoverflow.com/a/4264154
    }

    static inline auto exec(const char*)
    {
        return "s";
    }

    static inline auto exec(const std::string&)
    {
        return "s";
    }

    static inline auto exec(const std::string_view&)
    {
        return "s";
    }

    static inline const char* exec(const std::unique_ptr<char[]>& a_data)
    {
        return "s";
    }
};

} // namespace util
