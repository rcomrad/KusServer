#ifndef VERTEX2D_POS1_TEXTURE_POS2_HPP
#define VERTEX2D_POS1_TEXTURE_POS2_HPP
#include <vulkan/vulkan.hpp>

#include <initializer_list>

#include "glm/vec2.hpp"

namespace kusengine::render
{

struct Vertex2DAttributesP1UV1
{
    glm::vec2 pos;
    glm::vec2 text_pos;
};

bool
operator==(const Vertex2DAttributesP1UV1& left,
           const Vertex2DAttributesP1UV1& right);

class Vertex2DDescriptionP1UV1
{
public:
    static vk::VertexInputBindingDescription getBindingDescription();

    static std::vector<vk::VertexInputAttributeDescription>
    getAttributeDescriptions();
};
}; // namespace kusengine::render

#endif // VERTEX2D_POS1_TEXTURE_POS2_HPP
