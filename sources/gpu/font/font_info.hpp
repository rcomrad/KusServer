#pragma once

#include <array>
#include <string>

namespace gpu::font
{

class FontInfo
{
public:
    int size = 24;
    std::string name;
    std::array<int, 3> color = {255, 255, 255};
};

} // namespace gpu::font
