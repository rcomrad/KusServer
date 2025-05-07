#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

#include <initializer_list>

namespace kusengine
{

struct UniversalVertexAttributes
{
    glm::vec2 pos;
    // glm::vec3 color;

    static constexpr int count_floats = 2;
};

class VertexDescription
{
public:
    static VertexDescription& getInstance();

    vk::VertexInputBindingDescription getBindingDescription();

    std::array<vk::VertexInputAttributeDescription, 1>
    getAttributeDescriptions();

private:
    VertexDescription() = default;

    UniversalVertexAttributes m_unviersal_vertex_attributes;
};

class UniversalVertex
{
public:
    UniversalVertex() = default;

    UniversalVertex(float x, float y, float r = 0, float g = 0, float b = 0);

    UniversalVertex(const glm::vec2& position, const glm::vec3& color);

    UniversalVertex(const std::initializer_list<float>& init_list);

    UniversalVertex& setPosition(float x, float y);

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
