#include "render_system.hpp"

#include <iostream>

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/vertex/vertex_usings.hpp"
#include "utility/file_system/path_storage.hpp"
namespace kusengine::render
{

void
RenderSystem::setup(const DescriptorManager& desc_manager,
                    const vk::Extent2D& extent,
                    const vk::Format& format)
{
    m_extent = extent;
    m_format = format;

    setupDefaultRenderPass();
    setupDefaultPipeline(desc_manager);
}

vk::UniquePipelineLayout
RenderSystem::makePipelineLayout(
    const std::vector<vk::DescriptorSetLayout>& layouts)
{
    vk::PipelineLayoutCreateInfo layout_info;

    layout_info.setSetLayoutCount(layouts.size());
    layout_info.setPSetLayouts(layouts.data());

    return LOGICAL_DEVICE_INSTANCE.createPipelineLayoutUnique(layout_info);
}

void
RenderSystem::setupDefaultPipeline(const DescriptorManager& desc_manager)
{
    std::string sources_folder =
        util::PathStorage::getFolderPath("sources").value().data();

    PipelineConfigInfo info;
    info.extent = m_extent;

    std::vector<vk::DescriptorSetLayout> layouts = {
        desc_manager.getAllocator("default_vertex_shader").layout(),
        desc_manager.getAllocator("default_fragment_shader").layout()};

    info.pipeline_layout = makePipelineLayout(layouts);

    info.fragment_shader_path =
        sources_folder +
        "engine/render_manager/shaders/compiled/default_fragment_shader";

    info.vertex_shader_path =
        sources_folder +
        "engine/render_manager/shaders/compiled/default_vertex_shader";

    info.vertex_binding_description =
        VertexP1UV1::Description::getBindingDescription();
    info.vertex_attribute_descriptions =
        VertexP1UV1::Description::getAttributeDescriptions();

    m_pipelines["default"] = std::make_unique<Pipeline>(
        std::move(info), m_render_passes.at("default").get()->renderPass());
}

void
RenderSystem::setupDefaultRenderPass()
{
    RenderPassConfigInfo info;
    info.swap_chain_format = m_format;
}

void
RenderSystem::registerPipeline(std::string_view key,
                               std::string_view render_pass,
                               PipelineConfigInfo&& pipeline_info)
{
    if (m_render_passes.find(render_pass.data()) == m_render_passes.end())
    {
        std::cout << render_pass.data() << "does not exist\n";
    }
    else if (m_pipelines.find(key.data()) == m_pipelines.end())
    {
        m_pipelines[key.data()] = std::make_unique<Pipeline>(
            std::move(pipeline_info),
            m_render_passes[render_pass.data()].get()->renderPass());
    }
    else
    {
        std::cout << key.data() << "has already registered\n";
    }
}

void
RenderSystem::registerRenderPass(std::string_view key,
                                 const RenderPassConfigInfo& render_pass_info)
{
    if (m_render_passes.find(key.data()) == m_render_passes.end())
    {
        m_render_passes[key.data()] =
            std::make_unique<RenderPass>(render_pass_info);
    }
    else
    {
        std::cout << key.data() << "has already registered\n";
    }
}

void
RenderSystem::setExtent(const vk::Extent2D& extent)
{
    m_extent = extent;
}

void
RenderSystem::execute(const SwapChainFrame& frame,
                      const std::string& pass_name,
                      const vk::CommandBuffer& cmd)
{
    auto& pass = m_render_passes.at(pass_name);

    pass->begin(cmd, frame.getBuffer(pass_name), m_extent);

    // Здесь будет привязка пайплайнов и вызовы отрисовки

    pass->end(cmd);
}

} // namespace kusengine::render
