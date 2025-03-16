#include "window.hpp"

#include <iostream>

namespace kusengine
{

Window::Window(WindowCreateInfo& info)
{
    initWindow(info.width, info.height, info.title);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool
Window::wasWindowResized()
{
    return m_frame_buffer_resized_flag;
}

void
Window::resetWindowResizedFlag()
{
    m_frame_buffer_resized_flag = false;
}

VkExtent2D
Window::getExtent()
{
    return {static_cast<uint32_t>(m_width), static_cast<uint32_t>(m_height)};
}

void
Window::initWindow(WindowCreateInfo& info)
{
    initWindow(info.width, info.height, info.title);
}

void
Window::initWindow(int width, int height, const std::string& title)
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Failed to init glfw" << std::endl;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
}

bool
Window::isOpen()
{
    return !glfwWindowShouldClose(m_window);
}

int
Window::handleEvents()
{
    glfwPollEvents();

    int res = -1;

    if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        res = GLFW_KEY_RIGHT;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        res = GLFW_KEY_LEFT;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        res = GLFW_KEY_DOWN;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        res = GLFW_KEY_UP;
    }
    return res;
}

void
Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    glfwCreateWindowSurface(instance, m_window, 0, surface);
}

void
Window::framebufferResizeCallback(GLFWwindow* glfw_window_ptr,
                                  int width,
                                  int height)
{
    auto window =
        reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

    window->m_frame_buffer_resized_flag = true;

    window->m_width = width;

    window->m_height = height;
}

}; // namespace kusengine
