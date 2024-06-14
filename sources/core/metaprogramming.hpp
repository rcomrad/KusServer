#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <type_traits>

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

using namespace std::literals;

namespace core
{

template <typename T1, typename T2>
using isSameWeak = typename std::is_same<std::decay_t<T1>, std::decay_t<T2>>;

template <typename T, typename... Args>
using isOneOf = typename std::disjunction<isSameWeak<T, Args>...>;

template <typename T, typename... Args>
using isNotOneOf =
    typename std::negation<std::disjunction<isSameWeak<T, Args>...>>;

template <typename Base, typename Derived>
using isDerivedOf =
    typename std::is_base_of<std::decay_t<Base>, std::decay_t<Derived>>;

template <typename Arg>
using enableIf = typename std::enable_if_t<Arg::value>;

template <typename T1, typename T2>
using enableIfSame = typename std::enable_if_t<isSameWeak<T1, T2>::value>;

template <typename Base, typename Derived>
using enableIfDerivedOf =
    typename std::enable_if_t<core::isDerivedOf<Base, Derived>::value>;

template <class T>
using isSTDString = isOneOf<T, str::String>;

template <class T>
using isString = isOneOf<T, str::String, char*, const char*>;

template <class T>
using isNotString = isNotOneOf<T, str::String, char*, const char*>;

} // namespace core

//-------------------------------------------------------------------------------
