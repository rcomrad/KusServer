#ifndef SAFE_SQL_WRAPPER_HPP
#define SAFE_SQL_WRAPPER_HPP

#include <string>
#include <utility>

#include "domain/metaprogramming.hpp"
#include "text_data/to_string.hpp"

using namespace std::literals;

#define SQLWrapper give_me_error
#define wrap       give_me_error

namespace data
{

class SafeSQLWrapper
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
        auto s = text::toString(std::forward<S>(str));

        bool flag = false;
        int cnt   = 0;
        for (char c : s)
        {
            switch (c)
            {
                case '-':
                    ++cnt;
                    if (cnt == 1) break;
                case ';':
                case '\'':
                case '\"':
                    flag = true;
            }
        }
        if (flag) s.clear();

        return "\'" + s + "\'";
    }
};

template <typename T>
auto
safeWrap(T arg) noexcept
{
    return SafeSQLWrapper::convert(arg);
}

} // namespace data

#endif // !SAFE_SQL_WRAPPER_HPP
