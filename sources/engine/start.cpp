#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "start.hpp"

#include <vulkan/vulkan.h>

#include <iostream>


Start::Start()
{
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
    // {
    //     std::cout << "Successfully created vulkan instance" << std::endl;
    // }

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
