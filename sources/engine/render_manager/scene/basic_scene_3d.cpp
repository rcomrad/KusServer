#include "basic_scene_3d.hpp"

#include "engine/render_manager/render_manager.hpp"

namespace kusengine::render
{

Drawable3D_P1UV1_TRS
generateCube()
{
    auto& rm = RenderManager::getInstance();
    Drawable3D_P1UV1_TRS base{};
    base.setTexture(
        rm.getResource(RenderManager::ChooseResType<Texture>{}, "cube.png"));

    auto res = rm.getResource(
        RenderManager::ChooseResType<Mesh<Drawable3D_P1UV1_TRS::VertexType>>{},
        "cube");
    base.setMesh(res);
    return base;
}

void
BasicScene3D::create()
{
    auto cube = generateCube();

    for (int i = 0; i < 100; ++i)
    {
        drawables_3d_p1uv1_trs.emplace_back(
            std::make_unique<Drawable3D_P1UV1_TRS>(cube));
        drawables_3d_p1uv1_trs[i].get()->setPosition(i, i, i);
    }

    m_drawable_system.resetDrawables(drawables_3d_p1uv1_trs.begin(),
                                     drawables_3d_p1uv1_trs.end());

    for (auto& dr : drawables_3d_p1uv1_trs) dr->updModelMatrix();
}

void
BasicScene3D::update()
{
}

void
BasicScene3D::updMbddFrame(SwapChainFrame& frame) const
{
    auto& mbdd_vec = m_drawable_system.getMBDD();
    if (mbdd_vec.empty()) return;
    frame.updateMBDD(mbdd_vec);
}

void
BasicScene3D::bind(const vk::CommandBuffer& cmd) const
{
    m_drawable_system.bind(cmd);
}

void
BasicScene3D::draw(const vk::CommandBuffer& cmd,
                   const vk::PipelineLayout& layout) const
{
    m_drawable_system.draw(cmd, layout);
}
// void
// BasicScene3D::setRenderInfo(const RenderInfo& render_info)
// {
//     m_render_info = render_info;
// }

}; // namespace kusengine::render
