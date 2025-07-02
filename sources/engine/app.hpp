#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include <vector>

#include "engine/render_manager/scene/basic_scene_2d.hpp"
#include "engine/render_manager/scene/basic_scene_3d.hpp"
#include "window/window.hpp"

namespace kusengine
{
class App final
{
public:
    App() = default;

    bool initApp();

    void run();

    bool loopBody();

    static constexpr int HEIGHT = 520;

    static constexpr int WIDTH = 800;

private:
    // Renderer m_renderer;

    Window m_window;

    render::BasicScene3D m_scene;

    void compileShaders();

    void handleEvents(float el_time);

    // Time
    double getLoopTime();

    void FPSLimit(const double& loop_time);

    double m_target_frame_time;

    double m_last_time;

    // Gui

    gui::Mouse m_mouse;
};
}; // namespace kusengine

#endif // APP_HPP
