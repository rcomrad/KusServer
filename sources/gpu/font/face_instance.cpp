#include "face_instance.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include <cmath>

#include "freetype_instance.hpp"

gpu::font::FaceInstance::FaceInstance(FreeTypeInstance& a_lib,
                                      const std::string& a_font_name)
    : m_face(a_lib.createFace(a_font_name))
{
}

gpu::font::FaceInstance::~FaceInstance()
{
    FT_Done_Face(m_face);
}

void
gpu::font::FaceInstance::setPixelSize(int a_size)
{
    auto error = FT_Set_Pixel_Sizes(m_face, a_size, 0);
    if (error)
    {
        THROW("Unable to set font pixel size");
    }
}

gpu::font::Glyph
gpu::font::FaceInstance::renderGlyph(FT_ULong a_char_num)
{
    loadGlyph(a_char_num);
    auto error = FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
    if (error)
    {
        THROW("Unable to render glyph for char #%u",
              static_cast<uint32_t>(a_char_num));
    }
    return Glyph(*this);
}

const char*
gpu::font::FaceInstance::getGlyphData() const
{
    return reinterpret_cast<const char*>(m_face->glyph->bitmap.buffer);
}

float
gpu::font::FaceInstance::getScale() const
{
    static const float FREETYPE_16_16_SCALE = 65536.0f;
    static const float FREETYPE_26_6_SCALE  = 64.0f;

    return m_face->size->metrics.y_scale / FREETYPE_16_16_SCALE /
           FREETYPE_26_6_SCALE;
}

int
gpu::font::FaceInstance::getLeftPadding() const
{
    int32_t min_x = std::floor(m_face->bbox.xMin * getScale());
    return (min_x < 0) ? std::abs(min_x) : 0;
}

int
gpu::font::FaceInstance::getBaseline() const
{
    return std::ceil(m_face->bbox.yMax * getScale());
}

int
gpu::font::FaceInstance::getPitch() const
{
    return m_face->glyph->bitmap.pitch;
}

gpu::type::Dimensions
gpu::font::FaceInstance::getDimensions() const
{
    return gpu::type::Dimensions(m_face->glyph->bitmap.width,
                                 m_face->glyph->bitmap.rows);
}

gpu::type::CoordinateSize
gpu::font::FaceInstance::getBoxSize() const
{
    const auto scale = getScale();
    uint32_t width = std::ceil((m_face->bbox.xMax - m_face->bbox.xMin) * scale);
    uint32_t height =
        std::ceil((m_face->bbox.yMax - m_face->bbox.yMin) * scale);
    return type::CoordinateSize(width, height);
}

gpu::type::Coordinates
gpu::font::FaceInstance::getOffset() const
{
    int32_t x_offset = getLeftPadding() + m_face->glyph->bitmap_left;
    int32_t y_offset = getBaseline() - m_face->glyph->bitmap_top;
    return gpu::type::Coordinates(x_offset, y_offset);
}

void
gpu::font::FaceInstance::loadGlyph(FT_ULong a_char_num)
{
    auto error =
        FT_Load_Glyph(m_face, getGlyphIndex(a_char_num), FT_LOAD_DEFAULT);
    if (error)
    {
        THROW("Unable to load glyph for char #%u",
              static_cast<uint32_t>(a_char_num));
    }
}

int
gpu::font::FaceInstance::getGlyphIndex(FT_ULong a_char_num)
{
    auto result = FT_Get_Char_Index(m_face, a_char_num);
    if (!result)
    {
        THROW("No glyph found for char #%u", static_cast<uint32_t>(a_char_num));
    }
    return result;
}
