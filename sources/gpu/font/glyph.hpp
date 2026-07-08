#pragma once

#include <array>
#include <cstdint>

#include "gpu/sprite/pixel_array.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::font
{

class FaceInstance;

class Glyph
{
public:
    Glyph(const FaceInstance& a_face);

    sprite::PixelArray createPixelArray(const std::array<int, 3>& a_colors);

private:
    const char* m_data;

    int m_pitch;
    type::Dimensions m_dem;
    type::CoordinateSize m_box_size;
    type::Coordinates m_offset;
};

} // namespace gpu::font
