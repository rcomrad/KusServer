#include "render_system.hpp"

#include <iostream>

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/vertex/vertex_p2d_uv.hpp"
#include "engine/render_manager/vertex/vertex_p3d_uv.hpp"

namespace kusengine::render
{

void
RenderSystem::setup(const DescriptorManager& desc_manager,
                    const ShaderManager& shader_manager,
                    const vk::Extent2D& extent,
                    const vk::Format& format)
{
    setExtent(extent);
    m_format = format;

    setupDefaultRenderPass();
    setupDefaultPipelines(desc_manager, shader_manager);
}

const vk::PipelineLayout&
RenderSystem::getLayout(PipelineLayoutType type) const&
{
    return m_layout_storage.at(type).get();
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

    // TODO: Builder

    // layout

    std::array<vk::DescriptorSetLayout, 2> layouts = {
        desc_manager.getAllocator(DescriptorSetLayoutType::UBO_x_STORAGE)
            .layout(),
        desc_manager
            .getAllocator(DescriptorSetLayoutType::COMBINED_IMAGE_SAMPLER)
            .layout()};

    m_layout_storage
        [PipelineLayoutType::v_UBO_x_STORAGE__f_COMBINED_IMAGE_SAMPLER] =
            makePipelineLayout(layouts.size(), layouts.data());

    // for default 2D
    {
        PipelineConfigInfo info;

        info.pipeline_layout_type =
            PipelineLayoutType::v_UBO_x_STORAGE__f_COMBINED_IMAGE_SAMPLER;

        info.extent = m_extent;

        info.depth_test_enable = vk::False;

        info.pipeline_layout =
            m_layout_storage[info.pipeline_layout_type].get();

        info.vertex_shader_type   = ShaderType::DEFAULT_2D_VERTEX;
        info.fragment_shader_type = ShaderType::DEFAULT_FRAGMENT;

        info.vertex_binding_description = VertexP2DUV{}.getBindingDescription();
        info.vertex_attribute_descriptions =
            VertexP2DUV{}.getAttributeDescriptions();

        registerPipeline(VertexType::VERTEX_P2D_UV,
                         ModelUpdData::Type::MATRIX4x4,
                         Material::Type::TEXTURE_ZONE, "default",
                         std::move(info), shader_manager);
    }
    // for default 3D
    {
        PipelineConfigInfo info;

        info.pipeline_layout_type =
            PipelineLayoutType::v_UBO_x_STORAGE__f_COMBINED_IMAGE_SAMPLER;

        info.extent = m_extent;

        info.depth_test_enable = vk::True;

        std::array<vk::DescriptorSetLayout, 2> layouts = {
            desc_manager.getAllocator(DescriptorSetLayoutType::UBO_x_STORAGE)
                .layout(),
            desc_manager
                .getAllocator(DescriptorSetLayoutType::COMBINED_IMAGE_SAMPLER)
                .layout()};

        info.pipeline_layout =
            m_layout_storage
                [PipelineLayoutType::v_UBO_x_STORAGE__f_COMBINED_IMAGE_SAMPLER]
                    .get();

        info.vertex_shader_type   = ShaderType::DEFAULT_3D_VERTEX;
        info.fragment_shader_type = ShaderType::DEFAULT_FRAGMENT;

        info.vertex_binding_description = VertexP3DUV{}.getBindingDescription();
        info.vertex_attribute_descriptions =
            VertexP3DUV{}.getAttributeDescriptions();

        registerPipeline(VertexType::VERTEX_P3D_UV,
                         ModelUpdData::Type::MATRIX4x4,
                         Material::Type::TEXTURE_ZONE, "default",
                         std::move(info), shader_manager);
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
RenderSystem::registerPipeline(VertexType vertex_type,
                               ModelUpdData::Type model_upd_data_type,
                               Material::Type material_type,
                               std::string_view render_pass,
                               PipelineConfigInfo&& pipeline_info,
                               const ShaderManager& shader_manager)
{
    if (m_render_passes.find(render_pass.data()) == m_render_passes.end())
    {
        std::cout << render_pass.data() << "render pass does not exist\n";
    }
    else if (m_pipelines.find({vertex_type, model_upd_data_type,
                               material_type}) == m_pipelines.end())
    {
        m_pipelines[{vertex_type, model_upd_data_type, material_type}] =
            std::make_unique<Pipeline>(
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

void
RenderSystem::translateRenderPassesToFrame(SwapChainFrame& frame) const
{
    for (auto& pass : m_render_passes)
    {
        frame.addFrameBuffer(pass.first, pass.second.get()->renderPass(),
                             m_extent);
    }
}

const vk::PipelineLayout&
RenderSystem::bindPipeline(VertexType vertex_type,
                           ModelUpdData::Type model_upd_data_type,
                           Material::Type material_type,
                           const vk::CommandBuffer& cmd) const&
{
    PipelineKey pkey;
    if (m_pipelines.find(pkey = {vertex_type, model_upd_data_type,
                                 material_type}) != m_pipelines.end())
    {
        auto& p = m_pipelines.at(pkey);
        p->bind(cmd);
        return m_layout_storage.at(p->getPipeLayoutType()).get();
    }

    throw std::exception("pipeline does not exist\n");
}

void
RenderSystem::execute(const std::string& render_pass_name,
                      std::function<void()> binding,
                      const vk::CommandBuffer& cmd,
                      const vk::Framebuffer& frame_buffer) const
{
    auto& render_pass = m_render_passes.at(render_pass_name);

    render_pass.get()->begin(cmd, frame_buffer, m_extent);

    binding();

    render_pass.get()->end(cmd);
}

} // namespace kusengine::render
