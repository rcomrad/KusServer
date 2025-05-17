#ifndef PASS_GENERATOR_HPP
#define PASS_GENERATOR_HPP

//--------------------------------------------------------------------------------

#include <random>
#include <string>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace serv
{

class PassGenerator
{
public:
    HOLY_TRINITY_SINGLE(PassGenerator);

    static std::string generate(int aSize = 20) noexcept;

private:
    PassGenerator() noexcept;
    static PassGenerator& getInstance() noexcept;

    std::string mAlphabet;
    std::mt19937 mRandGenerator;
    std::uniform_int_distribution<uint32_t> mDistribution;
};

} // namespace serv

//--------------------------------------------------------------------------------

#endif // !PASS_GENERATOR_HPP
