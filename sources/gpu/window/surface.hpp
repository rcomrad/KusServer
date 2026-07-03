#pragma once

#include <vulkan/vulkan.hpp>
//*************************
#include <GLFW/glfw3.h>

#include "gpu/hardware/device.hpp"
#include "gpu/hardware/instance.hpp"
#include "gpu/utils/vk_converter.hpp"

namespace gpu::window
{

class Surface : public vk::SurfaceKHR
{
public:
    Surface(hard::Instance& a_instance,
            hard::Device& a_device,
            GLFWwindow& a_window_ptr);

    ~Surface();

    VK_CONVERTER(vk::SurfaceKHR);

private:
    hard::Instance& m_instance;

    static vk::SurfaceKHR create(hard::Instance& a_instance,
                                 hard::Device& a_device,
                                 GLFWwindow& a_window_ptr);
};

} // namespace gpu::window
