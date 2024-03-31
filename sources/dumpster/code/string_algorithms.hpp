#ifndef STRING_ALGORITHMS_HPP
#define STRING_ALGORITHMS_HPP

#include <string>

namespace code
{

class StringAlgorithms
{
public:
    static std::string normalizeName(const std::string& aName,
                                     bool aIsFirstCapital,
                                     bool aIsIdCapital = false) noexcept;
};

} // namespace code

#endif // !CODE_CLASS_HPP
