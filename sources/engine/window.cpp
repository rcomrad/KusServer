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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
}

bool
Window::isOpen()
{
    return !glfwWindowShouldClose(m_window);
}

void
Window::handleEvents()
{
    glfwPollEvents();
}

void
Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    glfwCreateWindowSurface(instance, m_window, 0, surface);
}

}; // namespace kusengine
