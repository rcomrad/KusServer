#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/render_manager/cache/cache.hpp"
#include "engine/render_manager/descriptors/resources/ubo_storage_resource_storage.hpp"
#include "engine/render_manager/dynamics_data/uniform_buffer_object.hpp"
#include "engine/render_manager/mesh/draw_info.hpp"
#include "engine/render_manager/mesh/mesh_combiner.hpp"
#include "engine/render_manager/model/complex_model.hpp"
#include "engine/render_manager/model/model.hpp"
#include "engine/render_manager/renderer/render_system.hpp"

#include "idrawable.hpp"

namespace kusengine::render
{

class DrawableSystem
{
public:
    virtual ~DrawableSystem() = default;

    DrawableSystem(ModelUpdData::Type mudt, int mud_size_butes);

    void setup(int frame_count, PipelineLayoutType plt);

    void draw(const vk::CommandBuffer& cmd,
              const render::RenderSystem& render_system,
              int frame_number,
              const vk::Framebuffer& frame_buffer) const;

    void setDrawablesAndLink(
        std::vector<std::unique_ptr<IDrawable>>& drawables);

    void addModel(const std::unique_ptr<Model>& model);

    // resources

    void setUBO(const UBO& ubo);

    void updateResourcesBuffers(int frame_number);

private:
    void setFrameCount(int count);

    void fillBufferAndLink(std::vector<std::unique_ptr<IDrawable>>& drawables);

    // cache

    mutable Cache<const Material*> m_material_cache;

    //

    ComplexModel m_complex_model;

    GpuVertexBuffer m_vertex_buffer;

    IndexBuffer m_index_buffer;

    std::vector<DrawInfo> m_draw_info_vec;

    // Instancing

    PipelineLayoutType m_pipeline_layout_type;

    int m_data_size_bytes;

    std::vector<char> m_models_upd_data;

    UBO m_ubo;

    std::vector<UboStorageResorceStorage> m_resource_storage_vec; // per frame
};
} // namespace kusengine::render

#endif // DRAWABLE_SYSTEM_HPP
