#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace kusengine
{

struct WindowCreateInfo
{
    int width;
    int height;
    std::string title;
};

class Window
{
public:
    Window() = default;

    Window(WindowCreateInfo& info);

    void initWindow(WindowCreateInfo& info);

    void initWindow(int width, int height, const std::string& title);

    VkExtent2D getExtent();

    ~Window();

    bool isOpen();

    bool wasWindowResized();

    void resetWindowResizedFlag();

    void handleEvents();

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

    std::vector<int> getKeyCodes();

private:
    static void framebufferResizeCallback(GLFWwindow* window,
                                          int width,
                                          int height);

    static void key_callback(GLFWwindow* window,
                             int key,
                             int scancode,
                             int action,
                             int mods);

    std::string m_title;

    int m_width;

    int m_height;

    bool m_frame_buffer_resized_flag;

    GLFWwindow* m_window;
};
}; // namespace kusengine

#endif // WINDOW_HPP
