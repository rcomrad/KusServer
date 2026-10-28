#include "kernel/tester/fixture.hpp"

#include <cstring>
#include <string>

#include "gpu/sprite/dds_structs.hpp"

namespace kustest
{

namespace
{

std::string
makeDDS(uint32_t a_width, uint32_t a_height)
{
    std::string content(sizeof(gpu::sprite::DDSFile) + 16, '\0');
    auto* file = reinterpret_cast<gpu::sprite::DDSFile*>(content.data());

    std::memcpy(file->magic, "DDS ", 4);
    file->header.size               = 124;
    file->header.flags              = 0x1007;
    file->header.width              = a_width;
    file->header.height             = a_height;
    file->header.pitch_or_linear_size = a_width * 4;
    file->header.pixel_format.size = 32;
    file->header.pixel_format.flags = 0x41;

    const char pixels[16] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x78,
                             0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x10};
    std::memcpy(file->data, pixels, sizeof(pixels));

    return content;
}

} // namespace

TEST(DDSTest, ParsesDimensionsAndPixelPointer)
{
    auto content = makeDDS(2, 2);

    auto pixels = gpu::sprite::pixelArrayFromDDS(std::move(content));

    EXPECT_EQ(pixels.size, gpu::type::CoordinateSize(2, 2));
    ASSERT_NE(pixels.data_ptr, nullptr);
    EXPECT_EQ(pixels.data_ptr, pixels.allocated_buffer.data() +
                                   sizeof(gpu::sprite::DDSFile));
    EXPECT_EQ(static_cast<unsigned char>(pixels.data_ptr[0]), 0x11);
    EXPECT_EQ(static_cast<unsigned char>(pixels.data_ptr[15]), 0x10);
}

} // namespace kustest
