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
    TexBase(std::unordered_map<std::string, std::vector<std::string>>*
                aVariables = nullptr) noexcept;
    HOLY_TRINITY_NOCOPY(TexBase);

protected:
    std::string getVariable(const std::string& aName) noexcept;

private:
    std::unordered_map<std::string, std::vector<std::string>>* mVariables;
};

}; // namespace tex

#endif // !TEX_BASE_HPP
