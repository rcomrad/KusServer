#include "vertex_p2d_uv.hpp"

namespace kusengine::render
{

VertexP2DUV::VertexP2DUV() : Vertex(VertexType::VERTEX_P2D_UV)
{
}

VertexP2DUV::VertexP2DUV(const glm::vec2 pos, const glm::vec2 uv)
    : VertexP2DUV()
{
    setPosition(pos);
    setUV(uv);
}

vk::VertexInputBindingDescription
VertexP2DUV::getBindingDescription() const
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = byteSize();
    description.inputRate = vk::VertexInputRate::eVertex;
    return description;
}

std::vector<vk::VertexInputAttributeDescription>
VertexP2DUV::getAttributeDescriptions() const
{
    std::vector<vk::VertexInputAttributeDescription> attribute_description(2);

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;
    attribute_description[0].offset   = offsetof(P2DUV, pos);

    // UV
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32Sfloat;
    attribute_description[1].offset   = offsetof(P2DUV, uv);

    return attribute_description;
}

void
VertexP2DUV::setPosition(const glm::vec2& pos) noexcept
{
    m_attributes.pos = pos;
}

void
VertexP2DUV::setUV(const glm::vec2& uv) noexcept
{
    m_attributes.uv = uv;
}

const glm::vec2&
VertexP2DUV::getUV() const& noexcept
{
    return m_attributes.uv;
}

}; // namespace kusengine::render
