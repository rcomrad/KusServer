#ifndef RECTANGLE_SHAPE_HPP
#define RECTANGLE_SHAPE_HPP

#include "engine/textures/texture.hpp"

#include "drawable.hpp"

namespace kusengine
{

class RectangleShape : public kusengine::Drawable
{
public:
    RectangleShape() = default;

    RectangleShape(const glm::vec2& position,
                   const glm::vec2& size);

    void setPosition(const glm::vec2& position);

    void setSize(const glm::vec2& size);

private:
    void createBeforeGenerateUnique() override;

    glm::vec2 m_position;

    glm::vec2 m_size;
};
}; // namespace kusengine

#endif // RECTANGLE_SHAPE_HPP
