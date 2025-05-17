#ifndef TEX_BASE_HPP
#define TEX_BASE_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "domain/holy_trinity.hpp"

namespace tex
{
class TexBase
{
public:
    TexBase(std::unordered_map<str::String, std::vector<str::String>>*
                aVariables = nullptr) noexcept;
    HOLY_TRINITY_NOCOPY(TexBase);

protected:
    str::String getVariable(const char* aName) noexcept;

private:
    std::unordered_map<str::String, std::vector<str::String>>* mVariables;
};

}; // namespace tex

#endif // !TEX_BASE_HPP
