#include "basic_scene.hpp"

namespace kusengine
{
namespace render
{

BasicScene::BasicScene()
{
    m_scene_name = "my_scene";

    std::get<ScenePartVector<Drawable_P1UV1_TRS>>(m_scenes).resize(1);
    std::get<ScenePartVector<Drawable_P1UV1_TRS>>(m_scenes)[0]
        .render_info.setName("random");
}

void
BasicScene::setSceneName(std::string_view new_scene_name)
{
    m_scene_name = new_scene_name.data();
}
// void
// BasicScene::setRenderInfo(const RenderInfo& render_info)
// {
//     m_render_info = render_info;
// }

// const RenderInfo&
// BasicScene::getRenderInfo() const noexcept
// {
//     return m_render_info;
// }
}; // namespace render
}; // namespace kusengine
