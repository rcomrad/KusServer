#include "string_algorithms.hpp"

str::String
code::StringAlgorithms::normalizeName(const char* aName,
                                      bool aIsFirstCapital,
                                      bool aIsIdCapital) noexcept
{
    str::String result = aName;

    if (aIsFirstCapital) result[0] = std::toupper(result[0]);

    int it = result.find('_');
    while (it != str::String::npos)
    {
        result[it + 1] = std::toupper(result[it + 1]);
        result.erase(it, 1);
        it = result.find('_');
    }

    it = result.find("Id");
    if (aIsIdCapital && it != str::String::npos)
    {
        result[it + 1] = std::toupper(result[it + 1]);
    }

    return result;
}
