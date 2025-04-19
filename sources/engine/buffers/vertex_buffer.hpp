#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <vector>

#include "buffer.hpp"

namespace kusengine
{
class VertexBuffer : public Buffer
{
public:
    VertexBuffer(const Device& device);

    void create(size_t size);

    void setVerteces(const std::vector<float>& verteces);

private:
};
}; // namespace kusengine

#endif // VERTEX_BUFFER_HPP
