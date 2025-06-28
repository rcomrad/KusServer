#ifndef INSTANCE_BUFFER_HPP
#define INSTANCE_BUFFER_HPP

#include <initializer_list>
#include <vector>

#include "buffer.hpp"

namespace kusengine
{
namespace render
{
class IndexBuffer : public Buffer
{
public:
    IndexBuffer();

    // void setIndices(const std::initializer_list<uint32_t>& vertices);
    // void setIndices(const std::vector<uint32_t>& vertices);

    void bind(const vk::CommandBuffer& command_buffer) const;

    void draw(const vk::CommandBuffer& command_buffer,
              uint32_t index_count,
              uint32_t instance_count,
              uint32_t first_index,
              uint32_t vertex_offset,
              uint32_t first_instance) const;

private:
};
}; // namespace render
}; // namespace kusengine

#endif // INSTANCE_BUFFER_HPP
