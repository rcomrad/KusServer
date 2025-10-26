#pragma once

#include <boost/preprocessor.hpp>

// // transform: x → decltype(x)
// #define DECLTYPE_OP(s, data, elem) decltype(elem)

// // build decltype list
// #define PRODUCER_DECLTYPE_SEQ(seq) \
//     BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(DECLTYPE_OP, _, seq))

// // main macro
// #define PRODUCER_IF_STATEMENT(seq)                                  \
//     if constexpr (std::is_constructible_v<RetT, DECLTYPE_SEQ(seq)>) \
//     {                                                               \
//         return RetT(BOOST_PP_SEQ_ENUM(seq));                        \
//     }

// // user-facing macro
// #define PRODUCER_IF(...)
// PRODUCER_IF_IMPL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

// transform: x → decltype(x)
#define DECLTYPE_OP(s, data, elem) decltype(elem)

// main macro
#define PRODUCER_IF_STATEMENT_IMPL(seq)                            \
    if constexpr (std::is_constructible_v < RetT,                  \
                  BOOST_PP_SEQ_TRANSFORM((DECLTYPE_OP, _, seq) >)) \
    {                                                              \
        return RetT(BOOST_PP_SEQ_ENUM(seq));                       \
    }

// user-facing macro
#define PRODUCER_IF_STATEMENT(...) \
    PRODUCER_IF_STATEMENT_IMPL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define PRODUCER(...)
template <typename ResultType>
ResultType
produce()
{
    PRODUCER_IF_STATEMENT(__VA_ARGS__)
}
