#include "heart.hpp"

#include "kernel/framework/include_me.hpp"

engine::Heart::Heart()
{
    VkSurfaceKHR raw_surface;
    if (glfwCreateWindowSurface(getInstance(), getWindow(), nullptr,
                                &raw_surface) != VK_SUCCESS)
    {
        THROW("Failed to create window surface");
    }
    m_surface = vk::UniqueSurfaceKHR(raw_surface, getInstance());
}
