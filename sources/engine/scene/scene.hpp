#ifndef SCENE_HPP
#define SCENE_HPP

#include "engine/drawable/drawable_system.hpp"
#include "engine/render_objects/objects_data/uniform_buffer_object.hpp"
#include "engine/renderer/swap_chain_frame.hpp"

#include "camera.hpp"

namespace kusengine
{

class Scene
{
public:
    Scene() = default;

    void create(float width, float height);

    void render(const vk::CommandBuffer& command_buffer,
                const vk::PipelineLayout& pipelayout,
                SwapChainFrame& frame) const;

    const UBO& ubo() const;

    const Camera2D& camera() const;

    void moveCamera(float x, float y, float z);

    void update(float time);

    void updateFrame(SwapChainFrame& frame) const;

    //

    const vk::ClearValue& clearColor() const;

private:
    vk::ClearValue m_clear_value;

    std::vector<std::unique_ptr<Drawable>> m_drawables;

    DrawableSystem m_system;

    UBO m_ubo;

    Camera2D m_camera;
};

}; // namespace kusengine

#endif // SCENE_HPP
