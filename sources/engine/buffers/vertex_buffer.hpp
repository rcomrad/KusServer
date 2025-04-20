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
    VertexBuffer(const Device& device);

    void setVertices(const std::initializer_list<float>& vertices);
    void setVertices(const std::vector<float>& vertices);

    void bind(const vk::CommandBuffer& command_buffer) const;

private:
    void checkBufferSize(size_t);
};
}; // namespace kusengine

#endif // VERTEX_BUFFER_HPP
