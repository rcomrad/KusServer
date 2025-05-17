#ifndef STRING_ALGORITHMS_HPP
#define STRING_ALGORITHMS_HPP

#include <string>

namespace code
{

class StringAlgorithms
{
public:
    static str::String normalizeName(const char* aName,
                                     bool aIsFirstCapital,
                                     bool aIsIdCapital = false) noexcept;
};

} // namespace code

#endif // !CODE_CLASS_HPP
