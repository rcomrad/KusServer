#include "scene.hpp"

#include "engine/render_manager/drawable/drawable_2d.hpp"
#include "engine/render_manager/mesh/mesh_combiner.hpp"
#include "engine/render_manager/model/complex_model.hpp"
#include "engine/render_manager/model/simple_model.hpp"
#include "engine/render_manager/render_manager.hpp"

#ifdef SCENE_HPP_IS_ON

namespace kusengine
{

Scene::Scene()
    : m_drawable_system(render::ModelUpdData::Type::MATRIX4x4,
                        sizeof(render::ModelMatrix))
{
}

void
Scene::create()
{
    m_drawable_system.setup(
        render::RenderManager::getInstance().frameCount(),
        render::PipelineLayoutType::v_UBO_x_STORAGE__f_COMBINED_IMAGE_SAMPLER);

    // create models

    auto& mesh_manager = render::RenderManager::getInstance().meshManager();

    std::unique_ptr<render::ModelUpdData> mud =
        std::make_unique<render::ModelMatrix>();

    std::unique_ptr<render::Model> model1 =
        std::make_unique<render::SimpleModel>(
            mud, mesh_manager.getMesh("stone_rectangle"));

    // // create Drawable

    auto drawable1 = std::make_unique<render::Drawable2D>(model1);

    m_drawables.emplace_back(std::move(drawable1));

    m_drawable_system.setDrawablesAndLink(m_drawables);
}

void
Scene::update()
{
}

void
Scene::updateBuffers(const render::UBO& ubo, int frame_number)
{
    m_drawable_system.setUBO(ubo);
    m_drawable_system.updateResourcesBuffers(frame_number);
}

void
Scene::draw(const vk::CommandBuffer& cmd,
            const render::RenderSystem& render_system,
            int frame_number,
            const render::SwapChainFrame& frame) const
{
    m_drawable_system.draw(cmd, render_system, frame_number,
                           frame.getBuffer("default"));
}

} // namespace kusengine
#endif //
