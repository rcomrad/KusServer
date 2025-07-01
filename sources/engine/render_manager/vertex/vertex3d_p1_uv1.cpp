#include "vertex3d_p1_uv1.hpp"

namespace kusengine::render
{

vk::VertexInputBindingDescription
Vertex3DDescriptionP1UV1::getBindingDescription()
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = sizeof(Vertex3DAttributesP1UV1);
    description.inputRate = vk::VertexInputRate::eVertex;
    return description;
}

std::vector<vk::VertexInputAttributeDescription>
Vertex3DDescriptionP1UV1::getAttributeDescriptions()
{
    std::vector<vk::VertexInputAttributeDescription> attribute_description(2);

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;
    attribute_description[0].offset   = offsetof(Vertex3DAttributesP1UV1, pos);

    // TextPos
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32Sfloat;
    attribute_description[1].offset =
        offsetof(Vertex3DAttributesP1UV1, text_pos);

    return attribute_description;
}

bool
operator==(const Vertex3DAttributesP1UV1& left,
           const Vertex3DAttributesP1UV1& right)
{
    return left.pos == right.pos && left.text_pos == right.text_pos;
}
}; // namespace kusengine::render
