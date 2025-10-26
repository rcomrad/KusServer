#pragma once

#include <vulkan/vulkan.hpp>
//*************************
#include <GLFW/glfw3.h>

namespace engine::window
{

class Surface
{
public:
    Surface(vk::Instance a_instance,
            vk::PhysicalDevice& a_device,
            GLFWwindow& a_window_ptr);

    vk::SurfaceKHR& get();

private:
    vk::UniqueSurfaceKHR m_surface;
};

} // namespace engine::window
