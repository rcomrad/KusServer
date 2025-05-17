#ifndef SAFE_SQL_WRAPPER_HPP
#define SAFE_SQL_WRAPPER_HPP

#include <string>
#include <utility>

#include "domain/metaprogramming.hpp"
#include "domain/to_string.hpp"

using namespace std::literals;

#define SQLWrapper give_me_error
#define wrap       give_me_error

namespace data
{

class SafeSQLWrapper
{
public:
    template <typename T, typename = dom::enableIf<dom::isNotString<T>>>
    static str::String convert(T&& arg) noexcept
    {
        return dom::toString(std::forward<T>(arg));
    }

    template <typename S, typename = dom::enableIf<dom::isString<S>>>
    static auto convert(S&& str) noexcept
    {
        auto s = dom::toString(std::forward<S>(str));

        bool flag = false;
        int cnt   = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            switch (s[i])
            {
                case '-':
                    ++cnt;
                    if (cnt == 1) break;
                case ';':
                case '\'':
                case '\"':
                    LOG_ERROR("penetration!", s[i], i);
                    flag = true;
                    break;
                default:
                    cnt = 0;
                    break;
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
