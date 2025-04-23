#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <initializer_list>
#include <vector>

#include "buffer.hpp"

namespace kusengine
{
class VertexBuffer : public Buffer
{
public:
    VertexBuffer() = default;

    void setVertices(const std::initializer_list<float>& vertices);
    void setVertices(const std::vector<float>& vertices);

    void bind(const vk::CommandBuffer& command_buffer) const;
    void draw(const vk::CommandBuffer& command_buffer,
              uint32_t vertex_count,
              uint32_t instance_count,
              uint32_t first_vertex,
              uint32_t first_instance) const;

private:
    void checkBufferSize(size_t) override;
};
}; // namespace kusengine

#endif // VERTEX_BUFFER_HPP
