#include "pass_generator.hpp"

//--------------------------------------------------------------------------------

serv::PassGenerator::PassGenerator() noexcept
{
    mAlphabet = "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "!#$%&()*+,./:<>?@[\\]^_`{|}~";

    mRandGenerator.seed(time(NULL));
    mDistribution = std::move(
        std::uniform_int_distribution<uint32_t>(0, mAlphabet.size() - 1));
}

serv::PassGenerator&
serv::PassGenerator::getInstance() noexcept
{
    static PassGenerator instance;
    return instance;
}

//--------------------------------------------------------------------------------

str::String
serv::PassGenerator::generate(int aSize) noexcept
{
    static PassGenerator& instance = getInstance();
    str::String result;
    while (result.size() < aSize)
    {
        int indx = instance.mDistribution(instance.mRandGenerator);
        result.push_back(instance.mAlphabet[indx]);
    }
    return result;
}
