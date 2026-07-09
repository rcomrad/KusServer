#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

#include "glyph.hpp"

namespace gpu::font
{

class FreeTypeInstance;

class FaceInstance
{
public:
    FaceInstance(FreeTypeInstance& a_lib, const std::string& a_font_name);
    ~FaceInstance();

    void setPixelSize(int a_size);

    Glyph renderGlyph(FT_ULong a_char_num);
    const char* getGlyphData() const;

    int getPitch() const;
    type::Dimensions getDimensions() const;
    type::CoordinateSize getBoxSize() const;
    type::Coordinates getOffset() const;

private:
    FT_Face m_face;

    float getScale() const;
    int getLeftPadding() const;
    int getBaseline() const;

    void loadGlyph(FT_ULong a_char_num);
    int getGlyphIndex(FT_ULong a_char_num);
};

} // namespace gpu::font
