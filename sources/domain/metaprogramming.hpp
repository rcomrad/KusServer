#ifndef DOM_METAPROGRAMMING_HPP
#define DOM_METAPROGRAMMING_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <type_traits>

//--------------------------------------------------------------------------------

using namespace std::literals;

namespace dom
{

template <typename T1, typename T2>
using isSameWeak = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>;

template <typename T, typename... Args>
using isOneOf = typename std::disjunction<isSameWeak<T, Args>...>;

template <typename Base, typename Derived>
using isDerivedOf =
    typename std::is_base_of<std::decay_t<Base>, std::decay_t<Derived>>;

template <typename Arg>
using enableIf = typename std::enable_if_t<Arg::value>;

template <typename T1, typename T2>
using enableIfSame = typename std::enable_if_t<isSameWeak<T1, T2>::value>;

template <typename Base, typename Derived>
using enableIfDerivedOf =
    typename std::enable_if_t<dom::isDerivedOf<Base, Derived>::value>;

template <class T>
using isSTDString = isOneOf<T, std::string>;

template <class T>
using isString = isOneOf<T, std::string, char*, const char*>;

} // namespace dom

//-------------------------------------------------------------------------------

#endif // !DOM_METAPROGRAMMING_HPP
