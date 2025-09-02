#ifndef VERTEX_PD3_UV_HPP
#define VERTEX_PD3_UV_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "vertex.hpp"

namespace kusengine::render
{

class VertexP3DUV final : public Vertex
{
public:
    VertexP3DUV();

    vk::VertexInputBindingDescription getBindingDescription() const override;

    std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions()
        const override;

    void setPosition(const glm::vec3& pos) noexcept;

    void setUV(const glm::vec2& uv) noexcept;
};

}; // namespace kusengine::render

#endif // VERTEX_PD3_UV_HPP
