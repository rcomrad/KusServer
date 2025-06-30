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
RenderSystem::makePipelineLayout(int count, vk::DescriptorSetLayout* data)
{
    vk::PipelineLayoutCreateInfo layout_info{};

    layout_info.setSetLayoutCount(count);
    layout_info.setPSetLayouts(data);

    return LOGICAL_DEVICE_INSTANCE.createPipelineLayoutUnique(layout_info);
}

void
RenderSystem::setupDefaultPipeline(const DescriptorManager& desc_manager)
{
    std::string sources_folder =
        util::PathStorage::getFolderPath("sources").value().data();

    PipelineConfigInfo info;
    info.extent = m_extent;

    std::array<vk::DescriptorSetLayout, 2> layouts = {
        desc_manager.getAllocator("default_vertex_shader").layout(),
        desc_manager.getAllocator("default_fragment_shader").layout()};

    info.pipeline_layout = makePipelineLayout(layouts.size(), layouts.data());

    info.fragment_shader_path = sources_folder +
                                "engine/render_manager/shaders/compiled/"
                                "default_fragment_shader.frag.spv";

    info.vertex_shader_path =
        sources_folder +
        "engine/render_manager/shaders/compiled/default_vertex_shader.vert.spv";

    info.vertex_binding_description =
        Vertex2DP1UV1::Description::getBindingDescription();
    info.vertex_attribute_descriptions =
        Vertex2DP1UV1::Description::getAttributeDescriptions();

    auto& r_pass = m_render_passes.at("default");

    m_pipelines["default"] =
        std::make_unique<Pipeline>(std::move(info), r_pass.get()->renderPass());
}

void
RenderSystem::setupDefaultRenderPass()
{
    RenderPassConfigInfo info;
    info.swap_chain_format     = m_format;
    m_render_passes["default"] = std::make_unique<RenderPass>(info);
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
RenderSystem::translateRenderPassesToFrame(SwapChainFrame& frame) const
{
    for (auto& pass : m_render_passes)
    {
        frame.addFrameBuffer(pass.first, pass.second.get()->renderPass(),
                             m_extent);
    }
}

void
RenderSystem::execute(const SwapChainFrame& frame,
                      const std::string& pass_name,
                      const vk::CommandBuffer& cmd,
                      const std::function<void()>& bd_lambda)
{
    auto& pass = m_render_passes.at(pass_name);

    pass->begin(cmd, frame.getBuffer(pass_name), m_extent);

    bd_lambda();

    pass->end(cmd);
}

const vk::PipelineLayout&
RenderSystem::bindPipeline(const std::string& key,
                           const vk::CommandBuffer& cmd) const&
{
    m_pipelines.at(key)->bind(cmd);
    return m_pipelines.at(key)->layout();
}

} // namespace kusengine::render
