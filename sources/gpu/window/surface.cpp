#include "surface.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

gpu::window::Surface::Surface(hard::Instance& a_instance,
                              hard::Device& a_device,
                              GLFWwindow& a_window_ptr)
    : vk::SurfaceKHR(create(a_instance, a_device, a_window_ptr)),
      m_instance(a_instance)
{
}

vk::SurfaceKHR
gpu::window::Surface::create(hard::Instance& a_instance,
                             hard::Device& a_device,
                             GLFWwindow& a_window_ptr)
{
    SCOPED_TRACE_INIT("surface");

    VkSurfaceKHR surface;
    auto res =
        glfwCreateWindowSurface(a_instance, &a_window_ptr, nullptr, &surface);
    if (res != VK_SUCCESS)
    {
        THROW("Failed to create surface");
    }
    return surface;
}

gpu::window::Surface::~Surface()
{
    m_instance.destroySurfaceKHR(toBase());
}
