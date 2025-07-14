#include "vertex_p3d_uv.hpp"

namespace kusengine::render
{

VertexP3DUV::VertexP3DUV() : Vertex(Type::VERTEX_P3D_UV, 5)
{
}

vk::VertexInputBindingDescription
VertexP3DUV::getBindingDescription() const
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = 32;
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
    attribute_description[0].offset   = 0;
    // offsetof(Vertex2DAttributesP1UV1, pos);

    // UV
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32Sfloat;
    attribute_description[1].offset   = 12;
    // offsetof(Vertex2DAttributesP1UV1, uv);

    return attribute_description;
}

void
VertexP3DUV::setPosition(const glm::vec3& pos) noexcept
{
    setValue(pos.x, 0);
    setValue(pos.y, 1);
    setValue(pos.z, 2);
}

void
VertexP3DUV::setUV(const glm::vec2& uv) noexcept
{
    setValue(uv.x, 3);
    setValue(uv.y, 4);
}

}; // namespace kusengine::render
