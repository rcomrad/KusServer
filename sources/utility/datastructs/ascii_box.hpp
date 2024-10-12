#pragma once

//------------------------------------------------------------------------------

#include "utility/type/base.hpp"

//------------------------------------------------------------------------------

namespace util
{

struct ASCIIBox
{
    int64_t data[2];

    ASCIIBox();
    ASCIIBox(const char* str);

    void set(const char* str);

    void set(int8_t num);
    bool get(int8_t num);
};

} // namespace util

//------------------------------------------------------------------------------
