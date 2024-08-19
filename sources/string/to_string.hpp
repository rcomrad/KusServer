// #ifndef TO_STRING_HPP
// #define TO_STRING_HPP

// //--------------------------------------------------------------------------------

// #include <string>

// #include "utility/common/metaprogramming.hpp"

// //--------------------------------------------------------------------------------

// namespace str
// {

// class ToString
// {
// public:
//     // static std::string convert(int aData) noexcept;
//     // static std::string convert(size_t aData) noexcept;
//     // static std::string convert(long long aData) noexcept;

//     // static std::string convert(float aData) noexcept;
//     // static std::string convert(double aData) noexcept;

//     static std::string convert(bool b) noexcept;
//     static std::string convert(const char* str) noexcept;

//     template <typename T,
//               typename = core::enableIf<
//                   core::isNotOneOf<T, bool, std::string, char*, const char*>>>
//     static std::string convert(T&& aData) noexcept
//     {
//         return std::to_string(aData);
//     }

//     template <typename S, typename = core::enableIf<core::isSTDString<S>>>
//     static auto convert(S&& str) noexcept
//     {
//         return std::forward<S>(str);
//     }
// };

// template <typename T>
// auto
// toString(T arg) noexcept
// {
//     return ToString::convert(arg);
// }

// } // namespace str

// //--------------------------------------------------------------------------------

// #endif // !TO_STRING_HPP
