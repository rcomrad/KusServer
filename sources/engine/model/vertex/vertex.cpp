#include "vertex.hpp"

namespace kusengine
{

VertexDescription&
VertexDescription::getInstance()
{
    static VertexDescription vertex_description;
    return vertex_description;
}

vk::VertexInputBindingDescription
VertexDescription::getBindingDescription()
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = sizeof(UniversalVertexAttributes);
    description.inputRate = vk::VertexInputRate::eVertex;
    return description;
}

std::vector<vk::VertexInputAttributeDescription>
VertexDescription::getAttributeDescriptions()
{
    std::vector<vk::VertexInputAttributeDescription> attribute_description(2);

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;
    attribute_description[0].offset = offsetof(UniversalVertexAttributes, pos);

    // TextPos
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32Sfloat;
    attribute_description[1].offset =
        offsetof(UniversalVertexAttributes, text_pos);

    return attribute_description;
}

// Vertex
UniversalVertex::UniversalVertex(float x, float y)
{
    setPosition(x, y);
}

UniversalVertex::UniversalVertex(const glm::vec2& position,
                                 const glm::vec3& color,
                                 const glm::vec2& text_position)
{
    setPosition(position.x, position.y);
}

UniversalVertex&
UniversalVertex::setPosition(float x, float y)
{
    m_attributes.pos = {x, y};
    return *this;
}

UniversalVertex&
UniversalVertex::setTexturePosition(float x, float y)
{
    m_attributes.text_pos = {x, y};
    return *this;
}

const UniversalVertexAttributes* const
UniversalVertex::data() const
{
    return &m_attributes;
}

}; // namespace kusengine
