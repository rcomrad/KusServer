#pragma once

//------------------------------------------------------------------------------

#include <string>
#include <string_view>

#include "kernel/utility/type/type_id.hpp"

//------------------------------------------------------------------------------

namespace util
{

struct ASCIIBox
{
    int64_t data[2];

    ASCIIBox();
    ASCIIBox(const char* str);
    ASCIIBox(std::string_view str);
    ASCIIBox(const std::string& str);

    void set(const char* str);

    void set(int8_t num);
    bool get(int8_t num);
};

} // namespace util

//------------------------------------------------------------------------------
