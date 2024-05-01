#pragma once

namespace str
{

class Separator
{
public:
    static bool isNewLine(char c) noexcept;
    static bool isNewWord(char c) noexcept;
};

} // namespace str
