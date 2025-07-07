#include "main_module.hpp"

#include <vulkan/vulkan.hpp>
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "kernel/framework/include_me.hpp"

auto module_name = "engine";

REG_MODULE(module_name, engine::MainModule);

engine::MainModule::MainModule() : core::ThreadModule(module_name)
{
}

void
engine::MainModule::threadInitialize()
{
    if (glfwInit() == GLFW_FALSE)
    {
        THROW("Failed to init GLFW");
    }
    else
    {
        LOG_INFO("GLFW initialized");
    }

    // m_window.create();

    // std::cout << "inside" << std::endl;

    // VkApplicationInfo appInfo = {};
    // appInfo.sType             = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // appInfo.pApplicationName  = "Pong";
    // appInfo.pEngineName       = "Ponggine";

    // VkInstanceCreateInfo instanceInfo = {};
    // instanceInfo.sType                =
    // VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; instanceInfo.pApplicationInfo =
    // &appInfo;

    // VkInstance instance;

    // VkResult result = vkCreateInstance(&instanceInfo, 0, &instance);
    // if (result == VK_SUCCESS)
    // {
    //     std::cout << "Successfully created vulkan instance" << std::endl;
    // }
    // else
    // {
    //     std::cout << "ERROR" << std::endl;
    // }
}

bool
engine::MainModule::threadLoopBody()
{
    return true;
}

void
engine::MainModule::threadTerminate()
{
    m_window.destroy();
    glfwTerminate();
    LOG_INFO("GLFW terminated");
}
