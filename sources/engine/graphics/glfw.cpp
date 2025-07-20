#include "glfw.hpp"

#include <vulkan/vulkan.hpp>
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "kernel/framework/include_me.hpp"

engine::GLFW::GLFW()
{
    if (glfwInit() == GLFW_FALSE)
    {
        THROW("Failed to init GLFW");
    }
    else
    {
        LOG_INFO("GLFW initialized");
    }
}

engine::GLFW::~GLFW()
{
    glfwTerminate();
    LOG_INFO("GLFW terminated");
}
