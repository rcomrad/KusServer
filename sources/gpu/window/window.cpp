#include "window.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

#include "gpu/utils/variable.hpp"

std::vector<gpu::event::Event> gpu::window::Window::m_events_buffer{
    event::MousePosition()};

gpu::window::Window::Window()
{
    SCOPED_TRACE_INIT("window itself");

    if (!glfwInit())
    {
        THROW("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // TODO: var str name
    core::IntVar win_width(VAR_NAME_WIN_WIDTH, 800, 10, 1920);
    core::IntVar win_height(VAR_NAME_WIN_HEIGHT, 600, 10, 1200);
    m_window = glfwCreateWindow(win_width.get(), win_height.get(),
                                "TODO: var str name", nullptr, nullptr);

    if (m_window == nullptr)
    {
        THROW("Failed to create GLFW window");
    }

    core::IntVar frame_width(VAR_NAME_FRAME_WIDTH, win_width.get(), 10, 1920);
    core::IntVar frame_height(VAR_NAME_FRAME_HEIGHT, win_height.get(), 10,
                              1200);
    updateSize();

    // glfwSetWindowUserPointer(m_window, &a_event_carrier);

    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    glfwSetFramebufferSizeCallback(m_window, resizeCallback);

    glfwSetCursorPosCallback(m_window, cursorPositionCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

    glfwSetKeyCallback(m_window, keyCallback);
}

gpu::window::Window::~Window()
{
    SCOPED_TRACE_TERM("window");
    glfwDestroyWindow(m_window);
}

void
gpu::window::Window::updateSize() const
{
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    KERNEL.setVariable(VAR_NAME_FRAME_WIDTH, width);
    KERNEL.setVariable(VAR_NAME_FRAME_HEIGHT, height);
}

void
gpu::window::Window::poolEvents(EventCarrier& a_event_carrier)
{
    glfwPollEvents();
    synchronizeEventBuffer(a_event_carrier);
}

GLFWwindow&
gpu::window::Window::get()
{
    return *m_window;
}

gpu::type::CoordinateSize
gpu::window::Window::getSize()
{
    core::IntVar height_var(VAR_NAME_FRAME_WIDTH);
    core::IntVar width_var(VAR_NAME_FRAME_HEIGHT);
    return type::CoordinateSize(height_var.get(), width_var.get());
}

void
gpu::window::Window::windowCloseCallback(GLFWwindow*)
{
    KERNEL.setVariable("is_running", false);
}

void
gpu::window::Window::resizeCallback(GLFWwindow* a_window, int, int)
{
    // KERNEL.setVariable(VAR_NAME_FRAME_WIDTH, a_width);
    // KERNEL.setVariable(VAR_NAME_FRAME_HEIGHT, a_height);

    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);
    // KERNEL.setVariable(VAR_NAME_FRAME_WIDTH, a_width);
    // KERNEL.setVariable(VAR_NAME_FRAME_HEIGHT, a_height);

    // int width, height;
    // glfwGetFramebufferSize(a_window, &width, &height);
    // KERNEL.setVariable(VAR_NAME_FRAME_WIDTH, a_width);
    // KERNEL.setVariable(VAR_NAME_FRAME_HEIGHT, a_height);
}

void
gpu::window::Window::cursorPositionCallback(GLFWwindow* a_window,
                                            double a_x,
                                            double a_y)
{
    auto& mouse_pos    = m_events_buffer.at(0).mousePosition;
    mouse_pos.coord.x  = a_x;
    mouse_pos.coord.y  = a_y;
    mouse_pos.is_valid = true;
}

void
gpu::window::Window::mouseButtonCallback(GLFWwindow* a_window,
                                         int a_button,
                                         int a_action,
                                         int s_mods)
{
    m_events_buffer.emplace_back(event::KeyInput{a_button, a_action});
}

void
gpu::window::Window::keyCallback(GLFWwindow* a_window,
                                 int a_key,
                                 int a_scancode,
                                 int a_action,
                                 int a_mods)
{
    m_events_buffer.emplace_back(event::KeyInput{a_key, a_action});
}

void
gpu::window::Window::synchronizeEventBuffer(EventCarrier& a_event_carrier)
{
    a_event_carrier.acquireWrite(std::move(m_events_buffer));
    if (m_events_buffer.empty())
    {
        m_events_buffer.emplace_back(event::MousePosition());
    }
}
