#ifndef TO_STRING_HPP
#define TO_STRING_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "metaprogramming.hpp"

//--------------------------------------------------------------------------------

namespace dom
{

class ToString
{
public:
    // static str::String convert(int aData) noexcept;
    // static str::String convert(size_t aData) noexcept;
    // static str::String convert(long long aData) noexcept;

    // static str::String convert(float aData) noexcept;
    // static str::String convert(double aData) noexcept;

    static str::String convert(bool b) noexcept;
    static str::String convert(const char* str) noexcept;

    template <typename T,
              typename = dom::enableIf<
                  dom::isNotOneOf<T, bool, str::String, char*, const char*>>>
    static str::String convert(T&& aData) noexcept
    {
        return std::to_string(aData);
    }

    template <typename S, typename = dom::enableIf<dom::isSTDString<S>>>
    static auto convert(S&& str) noexcept
    {
        return std::forward<S>(str);
    }
};

template <typename T>
auto
toString(T arg) noexcept
{
    return ToString::convert(arg);
}

} // namespace dom

//--------------------------------------------------------------------------------

#endif // !TO_STRING_HPP
