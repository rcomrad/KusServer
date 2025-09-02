#ifndef SCENE_HPP
#define SCENE_HPP

#include "engine/render_manager/drawable/drawable_system.hpp"
#include "engine/render_manager/drawable/idrawable.hpp"
#include "engine/render_manager/dynamics_data/uniform_buffer_object.hpp"

#define SCENE_HPP_IS_ON
#ifdef SCENE_HPP_IS_ON
//

//
namespace kusengine
{
class Scene
{
public:
    Scene();

    void create();

    void update();

    void updateBuffers(const render::UBO& ubo, int frame_number);

    void draw(const vk::CommandBuffer& cmd,
              const render::RenderSystem& render_system,
              int frame_number,
              const render::SwapChainFrame& frame) const;

private:
    std::vector<std::unique_ptr<render::IDrawable>> m_drawables;

    render::DrawableSystem m_drawable_system;
};
} // namespace kusengine
#endif // SCENE_HPP_IS_ON
#endif // SCENE_HPP
