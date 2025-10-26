#include "surface.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::window
{

Surface::Surface(vk::Instance a_instance,
                 vk::PhysicalDevice& a_device,
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
    m_surface = vk::UniqueSurfaceKHR(surface, a_instance);
}

vk::SurfaceKHR&
Surface::get()
{
    return *m_surface;
}

} // namespace engine::window
