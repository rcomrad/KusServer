#include "conversion.hpp"

// #include "kernel/framework/logger/basic/include_me.hpp"

int
util::Conversion::stoi(std::string_view a_str)
{
    // if (a_str.empty())
    // {
    //     THROW("Called util::stoi on empty string.")
    // }

    bool minus = a_str.at(0) == '-';
    int i      = minus ? 1 : 0;

    int result = 0;
    for (; i < a_str.size(); ++i)
    {
        result *= 10;
        result += a_str[i] - '0';
    }

    if (minus) result *= -1;
    return result;
}
