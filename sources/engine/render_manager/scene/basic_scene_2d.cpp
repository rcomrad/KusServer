#include "basic_scene_2d.hpp"

#include "engine/render_manager/render_manager.hpp"

namespace kusengine::render
{

void
BasicScene2D::create()
{

    auto& rm = RenderManager::getInstance();

    Drawable2D_P1UV1_TRS base{};
    base.setTexture(
        rm.getResource(RenderManager::ChooseResType<Texture>{}, "cat.png"));
    base.setMesh(rm.getResource(
        RenderManager::ChooseResType<Mesh<Drawable2D_P1UV1_TRS::VertexType>>{},
        "rectangle"));
    drawables_2d_p1uv1_trs.emplace_back(
        std::make_unique<Drawable2D_P1UV1_TRS>(base));

    drawables_2d_p1uv1_trs.emplace_back(
        std::make_unique<Drawable2D_P1UV1_TRS>(base));

    drawables_2d_p1uv1_trs.emplace_back(
        std::make_unique<Drawable2D_P1UV1_TRS>(base));

    m_drawable_system.resetDrawables(drawables_2d_p1uv1_trs.begin(),
                                     drawables_2d_p1uv1_trs.end());

    drawables_2d_p1uv1_trs[1]->setPosition(1.f, 1.f);
    drawables_2d_p1uv1_trs[2]->setPosition(-2.f, -1.f);
    drawables_2d_p1uv1_trs[2]->setSize(2.f, 1.f);

    for (auto& dr : drawables_2d_p1uv1_trs) dr->updModelMatrix();
}

void
BasicScene2D::updMbddFrame(SwapChainFrame& frame) const
{
    auto& mbdd_vec = m_drawable_system.getMBDD();
    if (mbdd_vec.empty()) return;
    frame.updateMBDD(mbdd_vec);
}

void
BasicScene2D::bind(const vk::CommandBuffer& cmd) const
{
    m_drawable_system.bind(cmd);
}

void
BasicScene2D::draw(const vk::CommandBuffer& cmd,
                   const vk::PipelineLayout& layout) const
{
    m_drawable_system.draw(cmd, layout);
}
// void
// BasicScene2D::setRenderInfo(const RenderInfo& render_info)
// {
//     m_render_info = render_info;
// }

}; // namespace kusengine::render
