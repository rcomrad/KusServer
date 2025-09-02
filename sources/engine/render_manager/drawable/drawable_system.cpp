#include "drawable_system.hpp"

#include <iostream>

#include "engine/render_manager/render_manager.hpp"
namespace kusengine::render
{

DrawableSystem::DrawableSystem(ModelUpdData::Type mudt, int mud_size_butes)
    : m_complex_model(mudt), m_data_size_bytes(mud_size_butes)
{
}

void
DrawableSystem::setup(int frame_count, PipelineLayoutType plt)
{
    setFrameCount(frame_count);
    m_pipeline_layout_type = plt;
}

void
DrawableSystem::draw(const vk::CommandBuffer& cmd,
                     const render::RenderSystem& render_system,
                     int frame_number,
                     const vk::Framebuffer& frame_buffer) const
{
    auto binding = [this, &cmd, &render_system, &frame_number]()
    {
        auto model_upd_data_type = m_complex_model.getModelUpdDataType();

        m_index_buffer.bind(cmd);

        m_resource_storage_vec[frame_number].bind(
            cmd, render_system.getLayout(m_pipeline_layout_type));

        m_material_cache.cache(nullptr);

        for (auto& di : m_draw_info_vec)
        {
            auto& layout =
                render_system.bindPipeline(di.vertex_type, model_upd_data_type,
                                           di.material->getType(), cmd);

            // materialCache(di.material, bind);

            if (m_material_cache.isInCache(di.material) == false)
            {
                m_material_cache.cache(di.material);
                di.material->bind(cmd, layout);
            }

            m_vertex_buffer.bind(cmd);
            m_index_buffer.draw(cmd, di.index_count, di.instance_count,
                                di.first_index, di.vertex_offset,
                                di.first_instance);
        }
    };

    render_system.execute("default", binding, cmd, frame_buffer);
}

void
DrawableSystem::setDrawablesAndLink(
    std::vector<std::unique_ptr<IDrawable>>& drawables)
{
    for (int i = 0; i < drawables.size(); ++i)
    {
        drawables[i]->pushToDrawableSystem(*this);
    }
    fillBufferAndLink(drawables);
}

void
DrawableSystem::addModel(const std::unique_ptr<Model>& model)
{
    m_complex_model.addModel(model);
}
void
DrawableSystem::fillBufferAndLink(
    std::vector<std::unique_ptr<IDrawable>>& drawables)
{
    MeshCombiner mesh_combiner;

    m_complex_model.combine(mesh_combiner);

    auto inds = mesh_combiner.fillBuffers(m_index_buffer, m_vertex_buffer,
                                          m_draw_info_vec);

    size_t cur_i = 0;

    m_models_upd_data.resize(m_data_size_bytes * m_complex_model.getCount());

    for (int i = 0; i < drawables.size(); ++i)
    {
        drawables[i]->linkUpdModelData(inds, cur_i, m_models_upd_data,
                                       m_data_size_bytes);
    }
}

void
DrawableSystem::setFrameCount(int count)
{
    m_resource_storage_vec.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        m_resource_storage_vec.emplace_back(
            RenderManager::getInstance().descriptorManager());
    }
}

void
DrawableSystem::setUBO(const UBO& ubo)
{
    m_ubo = ubo;
}

void
DrawableSystem::updateResourcesBuffers(int frame_number)
{
    m_resource_storage_vec[frame_number].updateBuffers(
        {.ubo = &m_ubo, .storage = &m_models_upd_data});
}

} // namespace kusengine::render
