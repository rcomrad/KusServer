#include "window.hpp"

#include "framework/include_me.hpp"

engine::Window::Window()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // TODO: var str name
    m_window = glfwCreateWindow(m_width.get(), m_window.get(),
                                "TODO: var str name", nullptr, nullptr);

    if (m_window == nullptr)
    {
        THROW("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, resizeCallback);
}

engine::Window::~Window()
{
    glfwDestroyWindow(m_window);
}

void
engine::Window::resizeCallback(GLFWwindow* a_glfw_window_ptr,
                               int a_width,
                               int a_height)
{
    // auto window =
    //     reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

    // window->m_frame_buffer_resized_flag = true;

    // window->m_width = width;

    // window->m_height = height;
}

// std::pair<int, int>
// engine::Window::getSize()
// {
//     KERNEL.getVariable();
// }

void
Window::calculateFrameRate()
{
    current_time = glfwGetTime();
    double delta = current_time - last_time;

    if (delta >= 1)
    {
        int framerate{std::max(1, int(num_frames / delta))};
        std::stringstream title;
        LOG_INFO("Running at %d fps.", framerate);
        last_time  = current_time;
        num_frames = -1;
        frame_time = float(1000.0 / framerate);
    }

    ++num_frames;
}

bool
Window::wasWindowResized() const
{
    return m_frame_buffer_resized_flag;
}

void
Window::resetWindowResizedFlag()
{
    m_frame_buffer_resized_flag = false;
}

vk::Extent2D
Window::getExtent() const
{
    return {static_cast<uint32_t>(m_width), static_cast<uint32_t>(m_height)};
}

bool
Window::createWindowSurface(const vk::Instance& instance,
                            VkSurfaceKHR& surface) const
{
    return glfwCreateWindowSurface(instance, m_window, nullptr, &surface) ==
           VK_SUCCESS;
}

void
Window::key_callback(GLFWwindow* window,
                     int key,
                     int scancode,
                     int action,
                     int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Запрос на закрытие окна
    }

    // Вывести сообщение при нажатии клавиши A
    if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
        {
            std::cout << "Key A was pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE)
        {
            std::cout << "Key A was released" << std::endl;
        }
        else if (action == GLFW_REPEAT)
        {
            std::cout << "Key A is being held down" << std::endl;
        }
    }
}

bool
Window::initWindow(int width, int height, const std::string& title)
{
    m_title  = title;
    m_width  = width;
    m_height = height;

    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Failed to init GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

    // glfwSetCursorPosCallback(m_window, mouse_callback);
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

bool
Window::isOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

GLFWwindow*
Window::get() const& noexcept
{
    return m_window;
}
}
; // namespace kusengine
