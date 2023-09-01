#ifndef TEX_FILE_HPP
#define TEX_FILE_HPP

#include <string>

#include "domain/holy_trinity.hpp"

namespace tex
{
class TexFile
{
public:
    TexFile(const std::string& aName) noexcept;
    HOLY_TRINITY_NOCOPY(TexFile);

    void addTable();
};

}; // namespace tex

#endif // !TEX_FILE_HPP
