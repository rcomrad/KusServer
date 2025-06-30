#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "render_manager/render_manager.hpp"
#include "render_manager/shaders/shaders/shader.hpp"
#include "utility/file_system/path_storage.hpp"

#define COMPILE_SHADERS

namespace kusengine
{

void
App::compileShaders()
{
    auto sources_path = util::PathStorage::getFolderPath("sources");

    std::string vertex_shader_path = sources_path.value().data();
    vertex_shader_path +=
        "engine/render_manager/shaders/spirv/default_vertex_shader.vert";

    std::string fragment_shader_path = sources_path.value().data();
    fragment_shader_path +=
        "engine/render_manager/shaders/spirv/default_fragment_shader.frag";

    auto dst_path = std::format("{}{}", sources_path.value(),
                                "engine/render_manager/shaders/compiled/");

    render::shader::compile(vertex_shader_path, dst_path);
    render::shader::compile(fragment_shader_path, dst_path);
}

bool
App::initApp()
{
#ifdef COMPILE_SHADERS
    compileShaders();
#endif

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
