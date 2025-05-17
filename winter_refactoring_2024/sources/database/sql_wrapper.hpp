#ifndef SQL_WRAPPER_HPP
#define SQL_WRAPPER_HPP

#include <string>
#include <utility>

#include "domain/metaprogramming.hpp"

#include "text_data/to_string.hpp"

using namespace std::literals;

#undef SQLWrapper
#undef wrap

namespace data
{

class SQLWrapper
{
public:
    template <typename T, typename = dom::enableIf<dom::isNotString<T>>>
    static std::string convert(T&& arg) noexcept
    {
        return text::toString(std::forward<T>(arg));
    }

    template <typename S, typename = dom::enableIf<dom::isString<S>>>
    static auto convert(S&& str) noexcept
    {
        return "\'" + text::toString(std::forward<S>(str)) + "\'";
    }
};

template <typename T>
auto
wrap(T arg) noexcept
{
    return SQLWrapper::convert(arg);
}

} // namespace data

#endif // !SQL_WRAPPER_HPP
