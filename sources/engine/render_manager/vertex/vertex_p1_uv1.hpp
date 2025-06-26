#ifndef VERTEX_POS1_TEXTURE_POS2_HPP
#define VERTEX_POS1_TEXTURE_POS2_HPP
#include <vulkan/vulkan.hpp>

#include <initializer_list>

#include "glm/vec2.hpp"

namespace kusengine
{
namespace render
{
struct VertexAttributesP1UV1
{
    glm::vec2 pos;
    glm::vec2 text_pos;
};

bool
operator==(const VertexAttributesP1UV1& left,
           const VertexAttributesP1UV1& right);

class VertexDescriptionP1UV1
{
public:
    static vk::VertexInputBindingDescription getBindingDescription();

    static std::vector<vk::VertexInputAttributeDescription>
    getAttributeDescriptions();
};

}; // namespace render
}; // namespace kusengine

#endif // VERTEX_POS1_TEXTURE_POS2_HPP
