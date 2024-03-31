#include "string_algorithms.hpp"

std::string
code::StringAlgorithms::normalizeName(const std::string& aName,
                                      bool aIsFirstCapital,
                                      bool aIsIdCapital) noexcept
{
    std::string result = aName;

    if (aIsFirstCapital) result[0] = std::toupper(result[0]);

    int it = result.find('_');
    while (it != std::string::npos)
    {
        result[it + 1] = std::toupper(result[it + 1]);
        result.erase(it, 1);
        it = result.find('_');
    }

    it = result.find("Id");
    if (aIsIdCapital && it != std::string::npos)
    {
        result[it + 1] = std::toupper(result[it + 1]);
    }

    return result;
}
