#ifndef BASIC_SCENE_HPP
#define BASIC_SCENE_HPP
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "engine/render_manager/drawable/drawable_system_usings.hpp"
#include "engine/render_manager/drawable/drawable_usings.hpp"
#include "engine/render_manager/renderer/renderer.hpp"

namespace kusengine::render
{

template <typename DrawableT>
struct ScenePart
{
    RenderInfo<DrawableT> render_info;
    std::vector<std::unique_ptr<DrawableT>> drawables_p1_uv1;
};

template <typename DrawableT>
using ScenePartVector = std::vector<ScenePart<DrawableT>>;

class BasicScene
{
public:
    void create();

    void setSceneName(std::string_view new_scene_name);

    // void upd

    void updMbddFrame(SwapChainFrame& frame) const;

    void bind(const vk::CommandBuffer& cmd) const;

    void draw(const vk::CommandBuffer& cmd,
              const vk::PipelineLayout& layout) const;

private:
    std::string m_scene_name;

    // RenderInfo<Drawable_P1UV1_TRS> render_info;
    std::vector<std::unique_ptr<Drawable_P1UV1_TRS>> drawables_p1_uv1;
    DrawableSystem_P1UV1_TRS m_drawable_system;
};

}; // namespace kusengine::render

#endif // BASIC_SCENE_HPP
