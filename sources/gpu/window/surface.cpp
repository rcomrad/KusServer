#include "surface.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/hardware/device.hpp"
#include "gpu/hardware/instance.hpp"

#include "window.hpp"

gpu::window::Surface::Surface(hard::Instance& a_instance,
                              hard::Device& a_device,
                              Window& a_window)
    : vk::SurfaceKHR(create(a_instance, a_device, a_window)),
      m_instance(a_instance)
{
}

vk::SurfaceKHR
gpu::window::Surface::create(hard::Instance& a_instance,
                             hard::Device& a_device,
                             Window& a_window)
{
    SCOPED_TRACE_INIT("surface");

    VkSurfaceKHR surface;
    auto res = glfwCreateWindowSurface(a_instance, &a_window->get(), nullptr,
                                       &surface);
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
