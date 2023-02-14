#ifndef DOM_MATH_HPP
#define DOM_MATH_HPP

//--------------------------------------------------------------------------------

#include <functional>
#include <string>

//--------------------------------------------------------------------------------

namespace dom
{
class Math
{
public:
    static uint64_t getHash(const std::string& aStr) noexcept;

    // constexpr static auto getStrHasher() noexcept
    // {
    //     return std::hash<std::string>{};
    // }
    // static constexpr auto hasher = std::hash<std::string>{};
    // static constexpr auto calculateStrHash(const std::string& aStr) noexcept
    // {
    //     // static auto hasher = getStrHasher();
    //     return hasher(aStr);
    // }
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DOM_MATH_HPP
