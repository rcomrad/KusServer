#pragma once

#include <string>

#include "gpu/utils/typedef.hpp"

namespace gpu::sprite
{

struct PixelArray
{
    const char* data_ptr;
    type::CoordinateSize size;
    std::string allocated_buffer;
};

} // namespace gpu::sprite
