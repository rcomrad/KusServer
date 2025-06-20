#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "engine/render_manager/renderer/render_way_types.hpp"

namespace kusengine
{
namespace render
{
class Renderer
{
public:
    Renderer() = default;

private:
    RenderWayTypes m_render_way_type;
};
}; // namespace render
}; // namespace kusengine

#endif // RENDERER_HPP
