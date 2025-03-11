#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <string>

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

    void handleEvents();

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

private:
    std::string m_title;

    int m_width;

    int m_height;

    GLFWwindow* m_window;
};
}; // namespace kusengine

#endif // WINDOW_HPP
