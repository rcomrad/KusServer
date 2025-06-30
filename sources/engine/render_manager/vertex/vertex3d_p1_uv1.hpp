#ifndef VERTEX3D_POS1_TEXTURE_POS2_HPP
#define VERTEX3D_POS1_TEXTURE_POS2_HPP
#include <vulkan/vulkan.hpp>

#include <initializer_list>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace kusengine::render
{

struct Vertex3DAttributesP1UV1
{
    glm::vec3 pos;
    glm::vec2 text_pos;
};

bool
operator==(const Vertex3DAttributesP1UV1& left,
           const Vertex3DAttributesP1UV1& right);

class Vertex3DDescriptionP1UV1
{
public:
    static vk::VertexInputBindingDescription getBindingDescription();

    static std::vector<vk::VertexInputAttributeDescription>
    getAttributeDescriptions();
};

}; // namespace kusengine::render

#endif // VERTEX3D_POS1_TEXTURE_POS2_HPP
