#include "render_way_storage.hpp"

#include "engine/render_manager/vertex/vertex.hpp"
#include "utility/file_system/path_storage.hpp"

namespace kusengine
{
namespace render
{

RenderWay
RenderWayStorage::getUniversalRenderWay(const vk::Extent2D& extent,
                                        vk::Format format)
{
    RenderWay universal_render_way;

    // Pipeline Info
    auto res_path =
        std::string(util::PathStorage::getFolderPath("sources").value());

    PipelineConfigInfo config_info;
    config_info.extent = extent;
    config_info.vertex_shader_path =
        res_path + "engine/shaders/compiled/vertex_shader.vert.spv";
    config_info.fragment_shader_path =
        res_path + "engine/shaders/compiled/fragment_shader.vert.spv";
    // --------- //

    // Desc Manager
    std::vector<std::vector<kusengine::render::DescriptorBindingData>> bindings(
        2);

    // First Layout
    DescriptorBindingData binding_data;

    binding_data.index = 0;
    binding_data.stage = vk::ShaderStageFlagBits::eVertex;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eUniformBuffer;
    bindings[0].emplace_back(binding_data);

    binding_data.index = 1;
    binding_data.stage = vk::ShaderStageFlagBits::eVertex;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eStorageBuffer;
    bindings[0].emplace_back(binding_data);

    binding_data.index = 0;
    binding_data.stage = vk::ShaderStageFlagBits::eFragment;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eCombinedImageSampler;
    bindings[1].emplace_back(binding_data);
    // --------- //

    universal_render_way.init<UniversalVertex>(format, config_info, bindings);

    return universal_render_way;
}

void
RenderWayStorage::create(const vk::Extent2D& extent, vk::Format format)
{
    m_pipelines[RenderWayTypes::UNIVERSAL] =
        getUniversalRenderWay(extent, format);
}

const RenderWay* const
RenderWayStorage::getRenderWay(RenderWayTypes type) const
{
    const RenderWay* res = nullptr;

    auto it = m_pipelines.find(type);
    if (it != m_pipelines.end())
    {
        res = &((*it).second);
    }
    return res;
}
}; // namespace render
}; // namespace kusengine
