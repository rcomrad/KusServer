#pragma once

// #include <vulkan/vulkan.hpp>
// #define GLFW_INCLUDE_VULKAN

// #include <GLFW/glfw3.h>

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
    Window();
    ~Window();

private:
    core::IntVar m_width;
    core::IntVar m_height;
    GLFWwindow* m_window;

    // static std::pair<int, int> getSize();

    static void resizeCallback(GLFWwindow* a_glfw_window_ptr,
                               int a_width,
                               int a_height);

    //--------------
    bool initWindow(const std::string& title);

    vk::Extent2D getExtent() const;

    ~Window();

    bool wasWindowResized() const;

    void resetWindowResizedFlag();

    // void handleEvents(Scene& scene, float time);

    bool createWindowSurface(const vk::Instance& instance,
                             VkSurfaceKHR& surface) const;

    void calculateFrameRate();

    GLFWwindow* get() const& noexcept;

private:
    static void key_callback(GLFWwindow* window,
                             int key,
                             int scancode,
                             int action,
                             int mods);

    // static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    std::string m_title;

    int m_width;

    int m_height;

    bool m_frame_buffer_resized_flag;

    // Time and Rate

    double last_time;
    double current_time;
    int num_frames;
    float frame_time;
};

}; // namespace engine
