#ifndef BASIC_CAMERA_HPP
#define BASIC_CAMERA_HPP

#include <glm/mat4x4.hpp>

#include "help_enums.hpp"

namespace kusengine::render
{
class BasicCamera
{
public:
    enum class Type
    {
        DEFAULT_CAMERA_2D,
        DEFAULT_CAMERA_3D
    };

    BasicCamera(Type type_arg, uint32_t width = 16u, uint32_t height = 9u);

    void setAspectRatio(float ar);

    void setAspectRatio(uint32_t width, uint32_t height);

    const glm::mat4& getMatrix() const& noexcept;

    virtual const glm::mat4& recalculate() & = 0;

    Type type() const noexcept;

protected:
    Type m_type;

    float m_aspect_ratio = 1.f;

    glm::mat4 m_matrix;
};
} // namespace kusengine::render

#endif // BASE_CAMERA_HPP
