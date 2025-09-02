#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace kusengine::gui
{
class Mouse
{
public:
    void init(GLFWwindow* window);

    const glm::dvec2& update(GLFWwindow* window);

    const glm::dvec2& offset() const noexcept;

private:
    glm::dvec2 m_last_position;
    glm::dvec2 m_offset = {0.f, 0.f};

    float m_sensitivity = 0.2f;
};
} // namespace kusengine::gui

#endif // MOUSE_HPP
