
#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

#include "domain/pair.hpp"

namespace file
{
struct Value
{
    std::string str;

    operator int() const noexcept;
    operator float() const noexcept;
    operator bool() const noexcept;

    operator std::string() const noexcept;

    operator dom::Pair<float>() const noexcept;

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
} // namespace file

#endif // !VALUE_HPP
