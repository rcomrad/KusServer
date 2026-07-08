#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

namespace gpu::font
{

class FreeTypeInstance
{
public:
    FreeTypeInstance();
    ~FreeTypeInstance();

    FT_Face createFace(const std::string& a_font_name);

private:
    FT_Library m_ft_lib;
};

} // namespace gpu::font
