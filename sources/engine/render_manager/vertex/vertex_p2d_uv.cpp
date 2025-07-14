#include "vertex_p2d_uv.hpp"

namespace kusengine::render
{

VertexP2DUV::VertexP2DUV() : Vertex(Type::VERTEX_P2D_UV, 4)
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
    description.stride    = 32;
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
    attribute_description[0].offset   = 0;
    // offsetof(Vertex2DAttributesP1UV1, pos);

    // UV
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32Sfloat;
    attribute_description[1].offset   = 8;
    // offsetof(Vertex2DAttributesP1UV1, uv);

    return attribute_description;
}

void
VertexP2DUV::setPosition(const glm::vec2& pos) noexcept
{
    setValue(pos.x, 0);
    setValue(pos.y, 1);
}

void
VertexP2DUV::setUV(const glm::vec2& uv) noexcept
{
    setValue(uv.x, 2);
    setValue(uv.y, 3);
}

}; // namespace kusengine::render
