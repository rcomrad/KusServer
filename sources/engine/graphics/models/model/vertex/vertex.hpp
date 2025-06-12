#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <vulkan/vulkan.hpp>

#include <initializer_list>

#include "glm/vec2.hpp"

namespace kusengine
{

struct UniversalVertexAttributes
{
    glm::vec2 pos;
    glm::vec2 text_pos;

    static constexpr int count_floats = 4;
};

bool
operator==(const UniversalVertexAttributes& left,
           const UniversalVertexAttributes& right);

class VertexDescription
{
public:
    static VertexDescription& getInstance();

    vk::VertexInputBindingDescription getBindingDescription();

    std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions();

private:
    VertexDescription() = default;

    UniversalVertexAttributes m_unviersal_vertex_attributes;
};

class UniversalVertex
{
    friend bool operator==(const UniversalVertex& left,
                           const UniversalVertex& right);

public:
    UniversalVertex() = default;

    UniversalVertex(float x, float y);

    UniversalVertex(const glm::vec2& position, const glm::vec2& text_position);

    UniversalVertex& setPosition(float x, float y);
    UniversalVertex& setTexturePosition(float x, float y);

    const UniversalVertexAttributes* const data() const;

    static constexpr inline int countFloats()
    {
        return UniversalVertexAttributes::count_floats;
    };

private:
    UniversalVertexAttributes m_attributes;
};

}; // namespace kusengine

#endif // VERTEX_HPP
