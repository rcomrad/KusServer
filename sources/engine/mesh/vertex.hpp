#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

namespace kusengine
{

struct VertexAttributes
{
    glm::vec2 position;
    glm::vec3 color;
    static constexpr int countFields()
    {
        return 2;
    }
};

class Vertex
{
public:
    static vk::VertexInputBindingDescription getBindingDescription();

    static std::array<vk::VertexInputAttributeDescription,
                      VertexAttributes::countFields()>
    getAttributeDescriptions();

private:
    VertexAttributes vertex_attributes;
};
}; // namespace kusengine

#endif // VERTEX_HPP
