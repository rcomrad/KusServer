#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "window.hpp"

namespace kusengine
{
class Renderer
{
public:
    Renderer() = default;

    void render();

    void draw();

    void initRenderer(Window& window);

private:
};
}; // namespace kusengine
#endif // RENDERER_HPP
