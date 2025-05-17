#pragma once

namespace str
{

class Separator
{
public:
    static bool newLine(char c) noexcept;
    static bool newWord(char c) noexcept;
    static bool variable(char c) noexcept;
    static bool space(char c) noexcept;
};

} // namespace str
