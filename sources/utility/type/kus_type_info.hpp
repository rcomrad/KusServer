#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <string_view>

#include "utility/common/metaprogramming.hpp"

#include "base.hpp"

//--------------------------------------------------------------------------------

namespace util
{

class TypeInfo
{
public:
    ENABLE_IF_SAME(T, int32_t)
    static TypeID getTypeId()
    {
        return TypeID::S_INT_32;
    }

    ENABLE_IF_SAME(T, uint32_t)
    static TypeID getTypeId()
    {
        return TypeID::U_INT_32;
    }

    ENABLE_IF_SAME(T, bool)
    static TypeID getTypeId()
    {
        return TypeID::BOOL;
    }

    ENABLE_IF_SAME(T, float)
    static TypeID getTypeId()
    {
        return TypeID::FLOAT;
    }

    ENABLE_IF_SAME(T, double)
    static TypeID getTypeId()
    {
        return TypeID::DOUBLE;
    }

    ENABLE_IF_SAME(T, char[])
    static TypeID getTypeId()
    {
        return TypeID::CHAR_PTR;
    }

    ENABLE_IF_SAME(T, std::string)
    static TypeID getTypeId()
    {
        return TypeID::STRING;
    }

    ENABLE_IF_SAME(T, std::string_view)
    static TypeID getTypeId()
    {
        return TypeID::STRING_VIEW;
    }
};

} // namespace util

//--------------------------------------------------------------------------------
