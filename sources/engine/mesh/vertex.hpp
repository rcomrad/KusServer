#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

namespace kusengine
{

struct UniversalVertexAttributes
{
    glm::vec2 pos;
    glm::vec3 color;

    static constexpr int count_floats = 5;
};

class VertexDescription
{
public:
    static VertexDescription& getInstance();

    vk::VertexInputBindingDescription getBindingDescription();

    std::array<vk::VertexInputAttributeDescription, 2>
    getAttributeDescriptions();

private:
    VertexDescription() = default;

    UniversalVertexAttributes m_unviersal_vertex_attributes;
};

class UniversalVertex
{
public:
    UniversalVertex& setPosition(float x, float y);

    UniversalVertex& setColor(float r, float g, float b);

    const float* const data() const;

    static constexpr inline int countFloats()
    {
        return UniversalVertexAttributes::count_floats;
    };

private:
    float m_data[UniversalVertexAttributes::count_floats];
};

}; // namespace kusengine

#endif // VERTEX_HPP
