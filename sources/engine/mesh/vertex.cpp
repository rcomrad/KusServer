#include "vertex.hpp"

namespace kusengine
{

vk::VertexInputBindingDescription
Vertex::getBindingDescription()
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = sizeof(VertexAttributes);
    description.inputRate = vk::VertexInputRate::eVertex;
    return description;
}

std::array<vk::VertexInputAttributeDescription, VertexAttributes::countFields()>
Vertex::getAttributeDescriptions()
{
    std::array<vk::VertexInputAttributeDescription, 2> attribute_description;

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;

    // Color
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32B32Sfloat;

    return attribute_description;
}
}; // namespace kusengine
