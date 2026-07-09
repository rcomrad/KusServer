#pragma once

#include "pixel_array.hpp"

namespace gpu::sprite
{

struct DDSPixelFormat
{
    uint32_t size;
    uint32_t flags;
    uint32_t four_cc;
    uint32_t rgb_bit_count;
    uint32_t r_bit_mask;
    uint32_t g_bit_mask;
    uint32_t b_bit_mask;
    uint32_t a_bit_mask;
};

struct DDSHeader
{
    uint32_t size;
    uint32_t flags;
    uint32_t height;
    uint32_t width;
    uint32_t pitch_or_linear_size;
    uint32_t depth;
    uint32_t mip_map_count;
    uint32_t reserved_1[11];
    DDSPixelFormat pixel_format;
    uint32_t caps_1;
    uint32_t caps_2;
    uint32_t caps_3;
    uint32_t caps_4;
    uint32_t reserved_2;
};

struct DDSFile
{
    char magic[4];
    DDSHeader header;
    char data[];
};

PixelArray
pixelArrayFromDDS(std::string&& a_file_content);

} // namespace gpu::sprite
