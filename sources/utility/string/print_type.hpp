#pragma once

//------------------------------------------------------------------------------

#include <typeindex>

#include "utility/type/base.hpp"

//------------------------------------------------------------------------------

namespace util
{

class PrintType
{
public:
    static const char* process(int arg) noexcept;
    static const char* process(double arg) noexcept;
    static const char* process(const char* arg) noexcept;

    static const char* process(std::type_index a_type) noexcept;

    static const char* process(TypeID a_type) noexcept;
};

} // namespace util

//------------------------------------------------------------------------------
