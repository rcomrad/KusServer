#include "window.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

namespace engine::window
{

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
    glfwSetFramebufferSizeCallback(m_window, resizeCallback);
}

Window::~Window()
{
    SCOPED_TRACE_TERM("window");
    glfwDestroyWindow(m_window);
}

bool
Window::isClosed()
{
    glfwPollEvents();
    return glfwWindowShouldClose(m_window);
}

void
Window::poolEvents()
{
    glfwPollEvents();
}

GLFWwindow&
Window::get()
{
    return *m_window;
}

void
Window::resizeCallback(GLFWwindow*, int a_width, int a_height)
{
    KERNEL.setVariable(VAR_NAME_WIDTH, a_width);
    KERNEL.setVariable(VAR_NAME_HEIGHT, a_height);
    KERNEL.setVariable(VAR_NAME_IS_RESIZED, true);
}

} // namespace engine::window
