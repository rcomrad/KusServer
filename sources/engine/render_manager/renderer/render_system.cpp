#include "render_system.hpp"

#include <iostream>

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/vertex/vertex_p2d_uv.hpp"
#include "engine/render_manager/vertex/vertex_p3d_uv.hpp"
#include "utility/file_system/path_storage.hpp"

namespace kusengine::render
{

void
RenderSystem::setup(const DescriptorManager& desc_manager,
                    const ShaderManager& shader_manager,
                    const vk::Extent2D& extent,
                    const vk::Format& format)
{
    m_extent = extent;
    m_format = format;

    setupDefaultRenderPass();
    setupDefaultPipelines(desc_manager, shader_manager);
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
RenderSystem::setupDefaultPipelines(const DescriptorManager& desc_manager,
                                    const ShaderManager& shader_manager)
{
    std::string shader_folder =
        util::PathStorage::getFolderPath("shaders").value().data();

    // TODO: Builder
    // for default 2D
    {
        PipelineConfigInfo info;
        info.extent = m_extent;

        info.depth_test_enable = vk::False;

        std::array<vk::DescriptorSetLayout, 2> layouts = {
            desc_manager.getAllocator(DescriptorSetLayoutType::UBO_x_STORAGE)
                .layout(),
            desc_manager
                .getAllocator(DescriptorSetLayoutType::COMBINED_IMAGE_SAMPLER)
                .layout()};

        info.pipeline_layout =
            makePipelineLayout(layouts.size(), layouts.data());
        info.vertex_shader_type   = ShaderType::DEFAULT_2D_VERTEX;
        info.fragment_shader_type = ShaderType::DEFAULT_FRAGMENT;

        info.vertex_binding_description = VertexP2DUV{}.getBindingDescription();
        info.vertex_attribute_descriptions =
            VertexP2DUV{}.getAttributeDescriptions();

        registerPipeline(
            {.inst_data_type = getInstanceDataType<InstanceDataMatrix>(),
             .vertex_type    = Vertex::Type::VERTEX_P2D_UV,
             .material_type  = Material::Type::TEXTURE},
            "default", std::move(info), shader_manager);
    }
    // for default 3D
    {
        PipelineConfigInfo info;
        info.extent = m_extent;

        info.depth_test_enable = vk::True;

        std::array<vk::DescriptorSetLayout, 2> layouts = {
            desc_manager.getAllocator(DescriptorSetLayoutType::UBO_x_STORAGE)
                .layout(),
            desc_manager
                .getAllocator(DescriptorSetLayoutType::COMBINED_IMAGE_SAMPLER)
                .layout()};

        info.pipeline_layout =
            makePipelineLayout(layouts.size(), layouts.data());
        info.vertex_shader_type   = ShaderType::DEFAULT_3D_VERTEX;
        info.fragment_shader_type = ShaderType::DEFAULT_FRAGMENT;

        info.vertex_binding_description = VertexP3DUV{}.getBindingDescription();
        info.vertex_attribute_descriptions =
            VertexP3DUV{}.getAttributeDescriptions();

        registerPipeline(
            {.inst_data_type = getInstanceDataType<InstanceDataMatrix>(),
             .vertex_type    = Vertex::Type::VERTEX_P3D_UV,
             .material_type  = Material::Type::TEXTURE},
            "default", std::move(info), shader_manager);
    }
}

void
RenderSystem::setupDefaultRenderPass()
{
    RenderPassConfigInfo info;
    info.swap_chain_format = m_format;

    registerRenderPass("default", info);
}

void
RenderSystem::registerPipeline(PipelineKey pkey,
                               std::string_view render_pass,
                               PipelineConfigInfo&& pipeline_info,
                               const ShaderManager& shader_manager)
{
    if (m_render_passes.find(render_pass.data()) == m_render_passes.end())
    {
        std::cout << render_pass.data() << "does not exist\n";
    }
    else if (m_pipelines.find(pkey) == m_pipelines.end())
    {
        m_pipelines[pkey] = std::make_unique<Pipeline>(
            std::move(pipeline_info),
            m_render_passes[render_pass.data()].get()->renderPass(),
            shader_manager);
    }
    else
    {
        std::cout << "pipeline has already registered\n";
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

// void
// RenderSystem::translateRenderPassesToFrame(SwapChainFrame& frame) const
// {
//     for (auto& pass : m_render_passes)
//     {
//         frame.addFrameBuffer(pass.first, pass.second.get()->renderPass(),
//                              m_extent);
//     }
// }

// void
// RenderSystem::execute(const SwapChainFrame& frame,
//                       const std::string& pass_name,
//                       const vk::CommandBuffer& cmd,
//                       const std::function<void()>& bd_lambda)
// {
//     auto& pass = m_render_passes.at(pass_name);

//     pass->begin(cmd, frame.getBuffer(pass_name), m_extent);

//     bd_lambda();

//     pass->end(cmd);
// }

const vk::PipelineLayout&
RenderSystem::bindPipeline(const PipelineKey& pkey,
                           const vk::CommandBuffer& cmd) const&
{
    if (m_pipelines.find(pkey) == m_pipelines.end())
    {
        throw std::exception("pipeline does not exist\n");
    }
    m_pipelines.at(pkey)->bind(cmd);
    return m_pipelines.at(pkey)->layout();
}

} // namespace kusengine::render
