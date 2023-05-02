#ifndef SQL_WRAPPER_HPP
#define SQL_WRAPPER_HPP

#include <string>
#include <utility>

#include "domain/metaprogramming.hpp"

using namespace std::literals;

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

#endif // !SQL_WRAPPER_HPP
