
#ifndef VALUE_HPP
#define VALUE_HPP

#include "core/pair.hpp"

#include "kus_string.hpp"

namespace str
{
struct Value
{
    str::String str;

    operator int() const noexcept;
    operator float() const noexcept;
    operator bool() const noexcept;

    // operator str::String() const noexcept;

    operator core::Pair<float>() const noexcept;

    enum class Type
    {
        Nun,
        Int,
        Float,
        Bool,
        String,
        PairInt,
        PairFloat
    };
    Type getType() const noexcept;
};
} // namespace str

#endif // !VALUE_HPP
