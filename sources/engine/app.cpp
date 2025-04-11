#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "utility/file_system/path_storage.hpp"

#include "engine_util.hpp"

namespace kusengine
{

bool
App::initApp()
{
    WindowCreateInfo window_info;
    window_info.width  = WIDTH;
    window_info.height = HEIGHT;
    window_info.title  = "Simple app window";

    m_window.initWindow(window_info);

    bool ok = m_renderer.initRenderer(m_window);

    if (!ok)
    {
        std::cout << "Renderer could not create!\n";
        return false;
    }

    m_target_frame_time = 1 / 150.0;

    return true;
};

double
App::getLoopTime()
{
    double current_time = glfwGetTime();

    return current_time - std::exchange(m_last_time, current_time);
}

void
App::FPSLimit(const double& loop_time)
{
    if (loop_time < m_target_frame_time)
    {
        double sleep_time = m_target_frame_time - loop_time;
        glfwWaitEventsTimeout(sleep_time); // Ожидание
    }
}

bool
App::loopBody()
{
    m_window.handleEvents();

    if (!m_window.isOpen())
    {
        // m_renderer.deviceWaitIdle();
        return false;
    }

    float x = 0, y = 0;

    double loop_time = getLoopTime();

    m_renderer.draw();

    FPSLimit(loop_time);

    return true;
}

void
App::run()
{
    while (m_window.isOpen())
    {
        loopBody();
    }
    m_renderer.deviceWaitIdle();
}
}; // namespace kusengine
