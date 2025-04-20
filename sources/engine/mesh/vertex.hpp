#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

namespace kusengine
{

struct VertexAttributesPositionColor
{
    glm::vec2 position;
    glm::vec3 color;
    static constexpr int countFields()
    {
        return 2;
    }
};

struct VertexAttributesPositionTexture
{
    glm::vec2 position;
    glm::vec4 texture;
    static constexpr int countFields()
    {
        return 2;
    }
};

template <typename VertexAttributes>
class Vertex
{
public:
    static Vertex& getInstance();

    vk::VertexInputBindingDescription getBindingDescription();

    std::array<vk::VertexInputAttributeDescription,
               VertexAttributesPositionColor::countFields()>
    getAttributeDescriptions();

private:
    Vertex() = default;

    VertexAttributesPositionColor vertex_attributes_pos_color;
};

template <typename VertexAttributes>
Vertex<VertexAttributes>&
Vertex<VertexAttributes>::getInstance()
{
    static Vertex<VertexAttributes> vertex;
    return vertex;
}

template <typename VertexAttributes>
vk::VertexInputBindingDescription
Vertex<VertexAttributes>::getBindingDescription()
{
    vk::VertexInputBindingDescription description;
    description.binding   = 0;
    description.stride    = sizeof(VertexAttributes);
    description.inputRate = vk::VertexInputRate::eVertex;
    return description;
}

///////// getAttributeDescriptions

template <>
std::array<vk::VertexInputAttributeDescription,
           VertexAttributesPositionColor::countFields()>
Vertex<VertexAttributesPositionColor>::getAttributeDescriptions()
{
    std::array<vk::VertexInputAttributeDescription,
               VertexAttributesPositionColor::countFields()>
        attribute_description;

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;
    attribute_description[0].offset =
        offsetof(VertexAttributesPositionColor, position);

    // Color
    attribute_description[1].offset =
        offsetof(VertexAttributesPositionColor, color);
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32B32Sfloat;

    return attribute_description;
}

template <>
std::array<vk::VertexInputAttributeDescription,
           VertexAttributesPositionTexture::countFields()>
Vertex<VertexAttributesPositionTexture>::getAttributeDescriptions()
{
    std::array<vk::VertexInputAttributeDescription,
               VertexAttributesPositionTexture::countFields()>
        attribute_description;

    // Pos
    attribute_description[0].binding  = 0;
    attribute_description[0].location = 0;
    attribute_description[0].format   = vk::Format::eR32G32Sfloat;
    attribute_description[0].offset =
        offsetof(VertexAttributesPositionTexture, position);

    // Texture
    attribute_description[1].offset =
        offsetof(VertexAttributesPositionTexture, texture);
    attribute_description[1].binding  = 0;
    attribute_description[1].location = 1;
    attribute_description[1].format   = vk::Format::eR32G32B32A32Sfloat;

    return attribute_description;
}

}; // namespace kusengine

#endif // VERTEX_HPP
