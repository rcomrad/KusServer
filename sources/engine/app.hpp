#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include <vector>

#include "engine/graphics/scene/scene.hpp"
#include "graphics/renderer/renderer.hpp"
#include "graphics/window/window.hpp"

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
    Renderer m_renderer;

    Window m_window;

    Scene m_scene;

    // Time

    void compileShaders();

    double getLoopTime();

    void FPSLimit(const double& loop_time);

    double m_target_frame_time;

    double m_last_time;
};
}; // namespace kusengine

#endif // APP_HPP
