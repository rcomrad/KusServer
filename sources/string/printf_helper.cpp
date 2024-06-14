// #include "printf_helper.hpp"

// #include <cstdio>

// //------------------------------------------------------------------------------

// void
// str::PrintfHelper::process(bool aData, char** aPtr) noexcept
// {
//     *aPtr += std::sprintf(*aPtr, aData ? "true" : "false");
// }

// void
// str::PrintfHelper::process(int aData, char** aPtr) noexcept
// {
//     *aPtr += std::sprintf(*aPtr, wrapper(aData), aData);
// }

// void
// str::PrintfHelper::process(double aData, char** aPtr) noexcept
// {
//     *aPtr += std::sprintf(*aPtr, wrapper(aData), aData);
// }

// void
// str::PrintfHelper::process(const char* aData, char** aPtr) noexcept
// {
//     char* cc = (char*)aData;
//     *aPtr += std::sprintf(*aPtr, wrapper(aData), aData);
// }

// //------------------------------------------------------------------------------

// auto
// str::PrintfHelper::wrapper(bool aData) noexcept
// {
//     return "";
// }

// auto
// str::PrintfHelper::wrapper(int aData) noexcept
// {
//     return "%d";
// }

// auto
// str::PrintfHelper::wrapper(double aData) noexcept
// {
//     return "%lf";
// }

// auto
// str::PrintfHelper::wrapper(const char* aData) noexcept
// {
//     return "%s";
// }

// //------------------------------------------------------------------------------
