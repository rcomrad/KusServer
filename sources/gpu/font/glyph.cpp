#include "glyph.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "face_instance.hpp"

gpu::font::Glyph::Glyph(const FaceInstance& a_face)
    : m_data(a_face.getGlyphData()),
      m_pitch(a_face.getPitch()),
      m_dem(a_face.getDimensions()),
      m_box_size(a_face.getBoxSize()),
      m_offset(a_face.getOffset())
{
}

gpu::sprite::PixelArray
gpu::font::Glyph::createPixelArray(const std::array<int, 3>& a_colors)
{
    sprite::PixelArray result;

    result.size            = m_box_size;
    const int32_t box_size = m_box_size.x * m_box_size.y;

    result.allocated_buffer.resize(box_size * 4, 0);
    result.data_ptr = result.allocated_buffer.c_str();
    auto& output    = result.allocated_buffer;

    for (uint32_t y = 0; y < m_dem.y; ++y)
    {
        for (uint32_t x = 0; x < m_dem.x; ++x)
        {
            // size_t source_indx = y * m_dem.x + x; // TODO: understand
            size_t source_indx = y * m_pitch + x;
            size_t dest_pixel =
                (y + m_offset.y) * m_box_size.x + (x + m_offset.x);
            size_t dest_indx = dest_pixel * 4;

            uint8_t alpha = m_data[source_indx];

            output.at(dest_indx + 0) = a_colors.at(0); // R
            output.at(dest_indx + 1) = a_colors.at(1); // G
            output.at(dest_indx + 2) = a_colors.at(2); // B
            output.at(dest_indx + 3) = alpha;          // A
        }
    }

    return result;
}
