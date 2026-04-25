#pragma once

//------------------------------------------------------------------------------

#include <string_view>

//------------------------------------------------------------------------------

namespace utils
{

class Conversion
{
public:
    Conversion() = delete;

    static int stoi(std::string_view a_str);
};

} // namespace utils

//------------------------------------------------------------------------------
