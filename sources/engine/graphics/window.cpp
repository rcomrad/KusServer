#include "window.hpp"

engine::Window::Window()
    : m_width("win_width", 10, 1920), m_height("win_height", 10, 1200)
//   ,
//   m_frame_cnt(0),
//   m_frame_rate(0),
//   m_current_time(glfwGetTime()),
//   m_last_time(glfwGetTime())
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // TODO: var str name
    m_window = glfwCreateWindow(m_width.get(), m_height.get(),
                                "TODO: var str name", nullptr, nullptr);

    if (m_window == nullptr)
    {
        THROW("Failed to create GLFW window");
    }

    // glfwSetWindowUserPointer(m_window, this);
    // glfwSetFramebufferSizeCallback(m_window, resizeCallback);

    // m_surface = vk::UniqueSurfaceKHR(
    //     static_cast<vk::SurfaceKHR>(surfaceRaw),
    //     vk::ObjectDestroy<vk::Instance, vk::DispatchLoaderDynamic>(instance);

    //     return glfwCreateWindowSurface(instance, m_window, nullptr, &surface)
    //     ==
    //            VK_SUCCESS;);
}

engine::Window::~Window()
{
    glfwDestroyWindow(m_window);
}

GLFWwindow*
engine::Window::getWindow() const
{
    return m_window;
}

// void
// engine::Window::resizeCallback(GLFWwindow* a_glfw_window_ptr,
//                                int a_width,
//                                int a_height)
// {
//     // auto window =
//     // reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

//     // window->m_frame_buffer_resized_flag = true;

//     // window->m_width = width;

//     // window->m_height = height;
// }

// int
// engine::Window::calculateFrameRate()
// {
//     m_current_time = glfwGetTime();

//     ++m_frame_cnt;
//     double delta = m_current_time - m_last_time;
//     if (delta >= 1)
//     {
//         m_frame_rate = int(m_frame_cnt / delta);
//         m_last_time  = m_current_time;
//         m_frame_cnt  = 0;
//     }

//     return m_frame_rate;
// }

// bool
// engine::Window::createWindowSurface(const vk::Instance& instance,
//                             VkSurfaceKHR& surface) const
// {
//     return glfwCreateWindowSurface(instance, m_window, nullptr, &surface) ==
//            VK_SUCCESS;
// }
