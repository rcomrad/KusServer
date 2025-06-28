#include "basic_scene.hpp"

#include "engine/render_manager/render_manager.hpp"

namespace kusengine::render
{

void
BasicScene::create()
{
    m_scene_name = "my_scene";

    auto& rm = RenderManager::getInstance();

    Drawable_P1UV1_TRS base{};

    base.setTexture(
        rm.getResource(RenderManager::ChooseResType<Texture>{}, "cat.png"));

    base.setMesh(rm.getResource(
        RenderManager::ChooseResType<Mesh<Drawable_P1UV1_TRS::VertexType>>{},
        "rectangle"));   

    drawables_p1_uv1.emplace_back(
        std::make_unique<Drawable_P1UV1_TRS>(std::move(base)));

    m_drawable_system.resetDrawables(drawables_p1_uv1.begin(),
                                     drawables_p1_uv1.end());
}

void
BasicScene::setSceneName(std::string_view new_scene_name)
{
    m_scene_name = new_scene_name.data();
}

void
BasicScene::updMbddFrame(SwapChainFrame& frame) const
{
    auto& mbdd_vec = m_drawable_system.getMBDD();
    if (mbdd_vec.empty()) return;
    frame.updateMBDD(mbdd_vec);
}

void
BasicScene::bind(const vk::CommandBuffer& cmd) const
{
    m_drawable_system.bind(cmd);
}

void
BasicScene::draw(const vk::CommandBuffer& cmd,
                 const vk::PipelineLayout& layout) const
{
    m_drawable_system.draw(cmd, layout);
}
// void
// BasicScene::setRenderInfo(const RenderInfo& render_info)
// {
//     m_render_info = render_info;
// }

}; // namespace kusengine::render
