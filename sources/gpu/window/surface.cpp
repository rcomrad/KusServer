#include "surface.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/hardware/device.hpp"
#include "gpu/hardware/instance.hpp"

#include "window.hpp"

gpu::window::Surface::Surface(hard::Instance& a_instance,
                              hard::Device& a_device,
                              Window& a_window)
    : SurfaceKHRBase(create(a_instance, a_device, a_window), a_instance)
{
}

void
gpu::window::SurfaceKHRDeleter::operator()(hard::Instance& a_instance,
                                           vk::SurfaceKHR& a_this) noexcept
{
    a_instance.destroySurfaceKHR(a_this);
}

vk::SurfaceKHR
gpu::window::Surface::create(hard::Instance& a_instance,
                             hard::Device& a_device,
                             Window& a_window)
{
    SCOPED_TRACE_INIT("surface");

    VkSurfaceKHR surface;
    auto res =
        glfwCreateWindowSurface(a_instance, &a_window.get(), nullptr, &surface);
    if (res != VK_SUCCESS)
    {
        THROW("Failed to create surface");
    }
    return surface;
}
