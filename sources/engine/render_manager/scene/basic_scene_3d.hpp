#ifndef BASIC_SCENE_3D_HPP
#define BASIC_SCENE_3D_HPP

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "engine/render_manager/drawable/drawable_system_usings.hpp"
#include "engine/render_manager/drawable/drawable_usings.hpp"

#include "basic_scene.hpp"

namespace kusengine::render
{

class BasicScene3D : public BasicScene
{
public:
    void create() override;

    void update();

    void updMbddFrame(SwapChainFrame& frame) const override;

    void bind(const vk::CommandBuffer& cmd) const override;

    void draw(const vk::CommandBuffer& cmd,
              const vk::PipelineLayout& layout) const override;

private:
    std::vector<std::unique_ptr<Drawable3D_P1UV1_TRS>> drawables_3d_p1uv1_trs;
    DrawableSystem3D_P1UV1_TRS m_drawable_system;
};

}; // namespace kusengine::render

#endif // BASIC_SCENE_3D_HPP
