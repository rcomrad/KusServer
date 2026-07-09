#include "dds_structs.hpp"

gpu::sprite::PixelArray
gpu::sprite::pixelArrayFromDDS(std::string&& a_file_content)
{
    PixelArray result;

    result.allocated_buffer = std::move(a_file_content);
    const char* temp_ptr    = result.allocated_buffer.data();
    auto& dds_file          = *reinterpret_cast<const DDSFile*>(temp_ptr);

    result.size.x = dds_file.header.width;
    result.size.y = dds_file.header.height;

    result.data_ptr = dds_file.data;

    return result;
}
