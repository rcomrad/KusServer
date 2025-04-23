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

std::array<vk::VertexInputAttributeDescription, 2>
VertexDescription::getAttributeDescriptions()
{
    std::array<vk::VertexInputAttributeDescription, 2> attribute_description;

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;
    attribute_description[0].offset = offsetof(UniversalVertexAttributes, pos);

    // Color
    attribute_description[1].offset =
        offsetof(UniversalVertexAttributes, color);
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32B32Sfloat;

    return attribute_description;
}

// Vertex

UniversalVertex&
UniversalVertex::setPosition(float x, float y)
{
    m_data[0] = x;
    m_data[1] = y;
    return *this;
}

UniversalVertex&
UniversalVertex::setColor(float r, float g, float b)
{
    m_data[2] = r;
    m_data[3] = g;
    m_data[4] = b;
    return *this;
}

const float* const
UniversalVertex::data() const
{
    return m_data;
}

}; // namespace kusengine
