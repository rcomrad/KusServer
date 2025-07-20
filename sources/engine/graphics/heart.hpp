#pragma once

#include "glfw.hpp"
#include "instance.hpp"
#include "window.hpp"

namespace engine
{

class Heart : public GLFW, public Window, public Instance
{
public:
    Heart();

    // std::vector<vk::PhysicalDevice> getAvailablePhysicalDevices() const;

private:
    vk::UniqueSurfaceKHR m_surface;
};

} // namespace engine
