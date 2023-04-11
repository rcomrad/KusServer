#ifndef TOKEN_HANDLER_HPP
#define TOKEN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <random>
#include <string>
#include <unordered_map>

//--------------------------------------------------------------------------------

namespace core
{

class TokenHandler
{
public:
    static TokenHandler& getInstance() noexcept;
    std::string generate() noexcept;
    bool check(const std::string& aToken, const std::string& aURL) noexcept;
    void clear() noexcept;

private:
    TokenHandler() noexcept;

    std::string mAlphabet;
    std::unordered_map<std::string, int> mTokens;

    std::mt19937 mRandGenerator;
    std::uniform_int_distribution<uint32_t> mDistribution;

    std::mutex mMutex;
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !TOKEN_HANDLER_HPP
