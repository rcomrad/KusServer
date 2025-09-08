#ifndef VERTEX_PD2_UV_HPP
#define VERTEX_PD2_UV_HPP

#include "glm/vec2.hpp"

#include "vertex.hpp"

namespace kusengine::render
{

struct P2DUV
{
    glm::vec2 pos;
    glm::vec2 uv;
};

class VertexP2DUV final : public Vertex<P2DUV>
{
public:
    VertexP2DUV();

    VertexP2DUV(const glm::vec2 pos, const glm::vec2 uv);

    vk::VertexInputBindingDescription getBindingDescription() const override;

    std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions()
        const override;

    void setPosition(const glm::vec2& pos) noexcept;

    void setUV(const glm::vec2& uv) noexcept;

    const glm::vec2& getUV() const& noexcept;
    const glm::vec2& getPos() const& noexcept;
};

}; // namespace kusengine::render

#endif // VERTEX_PD2_UV_HPP
