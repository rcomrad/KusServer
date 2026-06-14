#pragma once

#include <vulkan/vulkan.hpp>
//*************************
#include <GLFW/glfw3.h>

#include "engine/hardware/device.hpp"
#include "engine/hardware/instance.hpp"

namespace engine::window
{

class Surface
{
public:
    Surface(hard::Instance& a_instance,
            hard::Device& a_device,
            GLFWwindow& a_window_ptr);

    vk::SurfaceKHR& get();

private:
    vk::UniqueSurfaceKHR m_surface;
};

} // namespace engine::window
