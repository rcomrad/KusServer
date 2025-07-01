#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "render_manager/render_manager.hpp"
#include "utility/file_system/path_storage.hpp"

#define COMPILE_SHADERS

namespace kusengine
{

bool
App::initApp()
{

    try
    {
        m_window.initWindow(WIDTH, HEIGHT, "MyWindow");
        render::RenderManager::getInstance().init(m_window);
    }
    catch (std::exception& exc)
    {
        std::cout << exc.what();
        return false;
    }

    m_scene.create();

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

void
App::handleEvents(float el_time)
{
    glfwPollEvents();

    bool camera_action_flag = false;

    float x = 0, y = 0, z = 0;

    auto window = m_window.get();

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        x = -2 * el_time;

        camera_action_flag = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        x = 2 * el_time;

        camera_action_flag = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        y = -2 * el_time;

        camera_action_flag = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        y = 2 * el_time;

        camera_action_flag = true;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        z = el_time;

        camera_action_flag = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        z = -el_time;

        camera_action_flag = true;
    }
    if (camera_action_flag)
    {
        render::RenderManager::getInstance().moveCamera(x, y, z);
    }
}

bool
App::loopBody()
{
    // std::cout << "run\n";

    if (!m_window.isOpen())
    {
        // m_renderer.deviceWaitIdle();
        return false;
    }

    m_window.calculateFrameRate();

    float el_time = getLoopTime();

    handleEvents(el_time);

    render::RenderManager::getInstance().draw(&m_scene);

    return true;
}

void
App::run()
{
    initApp();
    while (m_window.isOpen())
    {
        loopBody();
    }
    // m_renderer.deviceWaitIdle();
}
}; // namespace kusengine
