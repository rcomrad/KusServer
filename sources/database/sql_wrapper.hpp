#ifndef SQL_WRAPPER_HPP
#define SQL_WRAPPER_HPP

#include <string>
#include <utility>

#include "domain/metaprogramming.hpp"
#include "domain/string.hpp"

namespace data
{
class SQLWrapper
{
public:
    SQLWrapper(int num);

    template <typename S, typename = dom::enableIf<dom::isString<S>>>
    SQLWrapper(S&& str)
    {
        value = "\'"s + std::forward<S>(str) + "\'"s;
    }
    SQLWrapper(const char* str);
    SQLWrapper(bool b);

    operator std::string&&();

private:
    std::string value;
};

template <typename T>
std::string
wrap(T arg, char delim = '\0')
{
    auto res = std::string(SQLWrapper(arg));
    if (delim != '\0')
    {
        res.push_back(delim);
    }
    return res;
}
} // namespace data

// std::string
// SQLMultyStringWrapper(std::string str) noexcept
// {
//     return str;
// }

// template <typename... Args>
// std::string
// SQLMultyStringWrapper(std::string str, Args&&... args) noexcept
// {
//     return str + SQLMultyStringWrapper(args...);
// }

// template <typename... Args>
// std::string
// SQLMultyWrapper(Args&&... args) noexcept
// {
//     auto res = SQLMultyStringWrapper(std::string(SQLWrapper(args), true)...);
//     res.resize(res.size() - 2);
// }

#endif // !SQL_WRAPPER_HPP
