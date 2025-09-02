#ifndef VERTEX_PD3_UV_HPP
#define VERTEX_PD3_UV_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "vertex.hpp"

namespace kusengine::render
{

struct P3DUV
{
    glm::vec3 pos;
    glm::vec2 uv;
};

class VertexP3DUV final : public Vertex<P3DUV>
{
public:
    VertexP3DUV();

    vk::VertexInputBindingDescription getBindingDescription() const override;

    std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions()
        const override;

    void setPosition(const glm::vec3& pos) noexcept;

    void setUV(const glm::vec2& uv) noexcept;

    const glm::vec2& getUV() const& noexcept;

private:
};

}; // namespace kusengine::render

#endif // VERTEX_PD3_UV_HPP
