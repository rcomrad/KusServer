#ifndef TO_STRING_HPP
#define TO_STRING_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace dom
{

const std::string&
toString(const std::string& aStr) noexcept;
std::string&
toString(std::string& aStr) noexcept;
std::string&&
toString(std::string&& aStr) noexcept;

std::string
toString(const char* c) noexcept;

std::string
toString(int aData) noexcept;
std::string
toString(size_t aData) noexcept;
std::string
toString(long long aData) noexcept;

std::string
toString(float aData) noexcept;
std::string
toString(double aData) noexcept;

std::string
toString(bool aData) noexcept;

} // namespace dom

//--------------------------------------------------------------------------------

#endif // !TO_STRING_HPP
