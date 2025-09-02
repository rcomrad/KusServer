#include "mouse.hpp"

#include <GLFW/glfw3.h>

#include <utility>
namespace kusengine::gui
{

void
Mouse::init(GLFWwindow* window)
{
    glfwGetCursorPos(window, &m_last_position.x, &m_last_position.y);
}

const glm::dvec2&
Mouse::offset() const noexcept
{
    return m_offset;
}

const glm::dvec2&
Mouse::update(GLFWwindow* window)
{
    glm::dvec2 current;
    glfwGetCursorPos(window, &current.x, &current.y);

    m_offset = (current - std::exchange(m_last_position, current));
    m_offset.x *= m_sensitivity;
    m_offset.y *= m_sensitivity;

    return m_offset;
}

} // namespace kusengine::gui
