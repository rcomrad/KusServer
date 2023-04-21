#ifndef DOM_METAPROGRAMMING_HPP
#define DOM_METAPROGRAMMING_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <type_traits>

//--------------------------------------------------------------------------------

namespace dom
{
    
template <typename T1, typename T2>
using isSameWeak = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>;

template <typename T, typename... Args>
using isOneOf = typename std::disjunction<isSameWeak<T, Args>...>;

template <typename Arg>
using enableIf = typename std::enable_if_t<Arg::value>;

template <typename T1, typename T2>
using enableIfSame = typename std::enable_if_t<isSameWeak<T1, T2>::value>;

template <class T>
using isSTDString = isOneOf<T, std::string>;

template <class T>
using isString = isOneOf<T, std::string, char*, const char*>;

} // namespace dom

//-------------------------------------------------------------------------------

#endif // !DOM_METAPROGRAMMING_HPP
