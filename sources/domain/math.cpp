#include "math.hpp"

//--------------------------------------------------------------------------------

#define ALPHABET_SIZE   (uint64_t(256))
#define HASH_STR_MODULE (uint64_t(1e14))

//--------------------------------------------------------------------------------

uint64_t
dom::Math::getHash(const std::string& aStr) noexcept
{
    uint64_t result = 0;
    for (const auto& i : aStr)
    {
        result += i * ALPHABET_SIZE;
        result %= HASH_STR_MODULE;
    }
    return result;
}

//--------------------------------------------------------------------------------
