#include "window.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

#include <iostream>

namespace engine::window
{

std::vector<Event> Window::m_events_buffer;

Window::Window(const core::IntVar& a_width, const core::IntVar& a_heigh)
{
    SCOPED_TRACE_INIT("window itself");

    if (!glfwInit())
    {
        THROW("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // TODO: var str name
    m_window = glfwCreateWindow(a_width.get(), a_heigh.get(),
                                "TODO: var str name", nullptr, nullptr);

    if (m_window == nullptr)
    {
        THROW("Failed to create GLFW window");
    }

    // glfwSetWindowUserPointer(m_window, &a_event_carrier);

    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    glfwSetFramebufferSizeCallback(m_window, resizeCallback);

    glfwSetCursorPosCallback(m_window, cursorPositionCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

    glfwSetKeyCallback(m_window, keyCallback);
}

Window::~Window()
{
    SCOPED_TRACE_TERM("window");
    glfwDestroyWindow(m_window);
}

// bool
// Window::isClosed()
// {
//     return glfwWindowShouldClose(m_window);
// }

void
Window::poolEvents(EventCarrier& a_event_carrier)
{
    glfwPollEvents();
    synchronizeEventBuffer(a_event_carrier);
}

GLFWwindow&
Window::get()
{
    return *m_window;
}

void
Window::windowCloseCallback(GLFWwindow*)
{
    KERNEL.setVariable("is_running", false);
}

void
Window::resizeCallback(GLFWwindow*, int a_width, int a_height)
{
    KERNEL.setVariable(VAR_NAME_WIDTH, a_width);
    KERNEL.setVariable(VAR_NAME_HEIGHT, a_height);
    KERNEL.setVariable(VAR_NAME_IS_RESIZED, true);
}

void
Window::cursorPositionCallback(GLFWwindow* a_window, double a_x, double a_y)
{
    auto& mouse_pos    = m_events_buffer.at(0).mousePosition;
    mouse_pos.x        = a_x;
    mouse_pos.y        = a_y;
    mouse_pos.is_valid = true;
}

void
Window::mouseButtonCallback(GLFWwindow* a_window,
                            int a_button,
                            int a_action,
                            int s_mods)
{
    m_events_buffer.emplace_back(KeyInput{a_button, a_action});
}

void
Window::keyCallback(GLFWwindow* a_window,
                    int a_key,
                    int a_scancode,
                    int a_action,
                    int a_mods)
{
    m_events_buffer.emplace_back(KeyInput{a_key, a_action});
}

void
Window::synchronizeEventBuffer(EventCarrier& a_event_carrier)
{
    a_event_carrier.acquireWrite(std::move(m_events_buffer));
    if (m_events_buffer.empty())
    {
        m_events_buffer.emplace_back(MousePosition{});
    }
}

} // namespace engine::window
