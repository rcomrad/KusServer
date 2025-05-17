#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <cstdint>

namespace proc
{
struct Limits
{
    uint64_t timeLimit;
    uint64_t memoryLimit;
};
} // namespace proc

#endif // !LIMITS_HPP
