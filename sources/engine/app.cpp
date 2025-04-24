#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "shaders/shaders/shader.hpp"
#include "utility/file_system/path_storage.hpp"

#define COMPILE_SHADERS

namespace kusengine
{

void
App::compileShaders()
{
    auto sources_path = util::PathStorage::getFolderPath("sources");

    std::string vertex_shader_path = sources_path.value().data();
    vertex_shader_path += "engine/shaders/spirv/vertex_shader.vert";

    std::string fragment_shader_path = sources_path.value().data();
    fragment_shader_path += "engine/shaders/spirv/fragment_shader.frag";

    auto dst_path =
        std::format("{}{}", sources_path.value(), "engine/shaders/compiled/");

    Shader::getInstance().compile(vertex_shader_path, dst_path);
    Shader::getInstance().compile(fragment_shader_path, dst_path);
}

bool
App::initApp()
{
#ifdef COMPILE_SHADERS
    compileShaders();
#endif

    if (!m_window.initWindow(WIDTH, HEIGHT, "Simple app window")) return false;

    if (!m_renderer.initRenderer(m_window)) return false;

    m_target_frame_time = 1 / 150.0;

    scene.create();

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

    m_renderer.drawFrame(m_window, scene);

    m_window.calculateFrameRate();

    return true;
}

void
App::run()
{
    while (m_window.isOpen())
    {
        m_window.handleEvents();
        // double loop_time = getLoopTime();
        m_renderer.drawFrame(m_window, scene);
        m_window.calculateFrameRate();
    }
    m_renderer.deviceWaitIdle();
}
}; // namespace kusengine
