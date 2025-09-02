#include "basic_camera.hpp"

namespace kusengine::render
{

BasicCamera::BasicCamera(Type type_arg, uint32_t width, uint32_t height)
    : m_type(type_arg)
{
    setAspectRatio(width, height);
}

void
BasicCamera::setAspectRatio(float ar)
{
    m_aspect_ratio = ar;
}

void
BasicCamera::setAspectRatio(uint32_t width, uint32_t height)
{
    if (height == 0) height = 1;
    m_aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
}

const glm::mat4&
BasicCamera::getMatrix() const& noexcept
{
    return m_matrix;
}

BasicCamera::Type
BasicCamera::type() const noexcept
{
    return m_type;
}

} // namespace kusengine::render
