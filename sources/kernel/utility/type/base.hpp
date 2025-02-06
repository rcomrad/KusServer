#pragma once

#include <cstdint>
#include <stddef.h>
#include <string>

using namespace std::literals;

using word_t = long;
using addr_t = uint64_t;

namespace util
{
enum class TypeID
{
    NUN,
    S_INT_8,
    S_INT_16,
    S_INT_32,
    S_INT_64,
    U_INT_8,
    U_INT_16,
    U_INT_32,
    U_INT_64,
    CHAR_PTR,
    STRING,
    STRING_VIEW,
    FLOAT,
    DOUBLE,
    BOOL,
    END
};
} // namespace util
