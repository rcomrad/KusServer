#ifndef RESULT_GENERATOR_HPP
#define RESULT_GENERATOR_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <random>
#include <string>
#include <unordered_map>

//--------------------------------------------------------------------------------

namespace core
{

class ResultGenerator
{
public:
    static std::string generate(int aCompetitionID) noexcept;

private:
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !RESULT_GENERATOR_HPP
