#pragma once

#include <vulkan/vulkan.hpp>
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

// #include <string>
// #include <vector>

// #include "engine/gui/mouse.hpp"
// #include "engine/render_manager/instance/instance.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine
{

// struct WindowCreateInfo
// {
//     int width;
//     int height;
//     std::string title;
// };

class Window
{
public:
    Window(const vk::UniqueInstance& m_instance);
    ~Window();

    int calculateFrameRate();

    // bool createWindowSurface(const vk::Instance& instance,
    //                          VkSurfaceKHR& surface) const;
private:
    core::IntVar m_width;
    core::IntVar m_height;
    GLFWwindow* m_window;
    // vk::UniqueHandle<vk::SurfaceKHR> m_surface;

    // int m_frame_cnt;
    // int m_frame_rate;
    // double m_current_time;
    // double m_last_time;

    // static std::pair<int, int> getSize();

    // static void resizeCallback(GLFWwindow* a_glfw_window_ptr,
    //                            int a_width,
    //                            int a_height);

    //--------------
};

}; // namespace engine
