#include "vertex_p3d_uv.hpp"

namespace kusengine::render
{

VertexP3DUV::VertexP3DUV() : Vertex(VertexType::VERTEX_P3D_UV)
{
}

vk::VertexInputBindingDescription
VertexP3DUV::getBindingDescription() const
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = byteSize();
    description.inputRate = vk::VertexInputRate::eVertex;
    return description;
}

std::vector<vk::VertexInputAttributeDescription>
VertexP3DUV::getAttributeDescriptions() const
{
    std::vector<vk::VertexInputAttributeDescription> attribute_description(2);

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32B32Sfloat;
    attribute_description[0].offset   = offsetof(P3DUV, pos);

    // UV
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32Sfloat;
    attribute_description[1].offset   = offsetof(P3DUV, uv);

    return attribute_description;
}

void
VertexP3DUV::setPosition(const glm::vec3& pos) noexcept
{
    m_attributes.pos = pos;
}

void
VertexP3DUV::setUV(const glm::vec2& uv) noexcept
{
    m_attributes.uv = uv;
}

const glm::vec2&
VertexP3DUV::getUV() const& noexcept
{
    return m_attributes.uv;
}

}; // namespace kusengine::render
