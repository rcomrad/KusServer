#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "sources/renderer/vk_renderer.hpp"

GLFWwindow*
create_window()
{
    GLFWwindow* window = NULL;

    window = glfwCreateWindow(640, 480, "Triangle", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

// int
// run_window(VkContext* vk_context, GLFWwindow* window, GameState* game_state)
// {

//     return 0;
// }

int
main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* glf_window = create_window();

    VkContext vk_context;
    GameState game_state;

    init_game(&game_state);

    vk_context.surface = VK_NULL_HANDLE;

    if (!vk_init(&vk_context, glf_window))
    {
        std::cout << "vk_init returned false\n";
        return -1;
    };

    while (!glfwWindowShouldClose(glf_window))
    {
        glfwPollEvents();

        float x = 0, y = 0;

        if (glfwGetKey(glf_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            x = 0.01;
        }
        if (glfwGetKey(glf_window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            x = -0.01;
        }
        if (glfwGetKey(glf_window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            y = 0.01;
        }
        if (glfwGetKey(glf_window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            y = -0.01;
        }

        update_game(&game_state, x, y);

        if (!vk_render(&vk_context, &game_state)) return -1;
    }

    // run_window(&vk_context, glf_window, &game_state);

    // vkDestroySurfaceKHR(vk_context.instance, vk_context.surface, 0);
    return 0;
}