#include "main_module.hpp"

// #include <vulkan/vulkan.h>

#include <iostream>

auto module_name = "engine";

REG_MODULE(module_name, engine, MainModule);

engine::MainModule::MainModule() : core::ThreadModule(module_name)
{
}

void
engine::MainModule::threadInitialize()
{
    std::cout << "inside" << std::endl;

    // VkApplicationInfo appInfo = {};
    // appInfo.sType             = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // appInfo.pApplicationName  = "Pong";
    // appInfo.pEngineName       = "Ponggine";

    // VkInstanceCreateInfo instanceInfo = {};
    // instanceInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // instanceInfo.pApplicationInfo     = &appInfo;

    // VkInstance instance;

    // VkResult result = vkCreateInstance(&instanceInfo, 0, &instance);
    // if (result == VK_SUCCESS)
    {
        std::cout << "Successfully created vulkan instance" << std::endl;
    }
    // else
    {
        std::cout << "ERROR" << std::endl;
    }
}

bool
engine::MainModule::threadLoopBody()
{
    return false;
}

void
engine::MainModule::threadTerminate()
{
}
