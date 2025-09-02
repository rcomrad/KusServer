#ifndef MODEL_SYSTEM_HPP
#define MODEL_SYSTEM_HPP
#include <engine/render_manager/buffers/gpu_buffer.hpp>
#include <engine/render_manager/buffers/index_buffer.hpp>

#include <memory>
#include <utility>
#include <vector>

#include "engine/render_manager/renderer/render_system.hpp"

#include "bind_info.hpp"
#include "model.hpp"

namespace kusengine::render
{

template <typename Model_t>
class ModelSystem
{
public:
    void combine(const std::vector<std::unique_ptr<Model_t>>& models);

    void draw(const vk::CommandBuffer& cmd,
              const RenderSystem& render_system) const;

private:
    void fillBuffers(
        const std::vector<
            std::pair<const Mesh<typename Model_t::Vertex_t>*, int>>& meshes);

    InstanceDataType inst_data_type;

    std::vector<typename Model_t::InstanceData_t> m_instance_data_vec;

    std::vector<DrawInfo> draw_info_vector;
    std::vector<BindPipelineInfo> bind_info_vector;

    GpuVertexBuffer m_vertex_buffer;
    IndexBuffer m_index_buffer;
};

template <typename Model_t>
void
ModelSystem<Model_t>::combine(
    const std::vector<std::unique_ptr<Model_t>>& models)
{
    assert(models.size() > 0);

    inst_data_type = getInstanceDataType<Model_t::InstanceData_t>();

    std::vector<std::pair<const Mesh<typename Model_t::Vertex_t>*, int>>
        all_meshes;

    for (int i = 0; i < models.size(); ++i)
    {
        models[i]->pushTo(all_meshes);
    }

    fillBuffers(all_meshes);
}

template <typename Model_t>
void
ModelSystem<Model_t>::fillBuffers(
    const std::vector<std::pair<const Mesh<typename Model_t::Vertex_t>*, int>>&
        meshes)
{
    bind_info_vector.resize(meshes.size());

    std::vector<float> all_verts;
    std::vector<uint32_t> all_inds;

    DrawInfo draw_info;

    uint32_t inst_count = 0;

    for (int i = 0; i < meshes.size(); ++i)
    {
        const Mesh<typename Model_t::Vertex_t>*& mesh = meshes[i].first;

        DrawInfo di = {.instance_count = meshes[i].second,
                       .first_instance = inst_count};

        BindPipelineInfo bpi = {
            .pipeline_key = {
                .inst_data_type =
                    getInstanceDataType<typename Model_t::InstanceData_t>()}};

        mesh->pushDataTo(all_verts, all_inds, draw_info_vector,
                         bind_info_vector);

        inst_count += meshes[i].second;
    }
}

template <typename Model_t>
void
ModelSystem<Model_t>::draw(const vk::CommandBuffer& cmd,
                           const RenderSystem& render_system) const
{
    m_vertex_buffer.bind(cmd);
    m_index_buffer.bind(cmd);

    for (int i = 0; i < bind_info_vector.size(); ++i)
    {
        auto& bind_info = bind_info_vector[i];
        auto& draw_info = draw_info_vector[i];

        render_system.bindPipeline(bind_info.pipeline_key, cmd);

        m_index_buffer.draw(cmd, draw_info.index_count,
                            draw_info.instance_count, draw_info.first_index,
                            draw_info.vertex_offset, draw_info.first_instance);
    }
}

} // namespace kusengine::render

#endif // MODEL_SYSTEM_HPP
