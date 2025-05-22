#include "render_pass.hpp"

#include "engine/render_objects/model/vertex/vertex.hpp"

namespace kusengine
{

const GraphicsPipeline&
RenderPass::graphicsPipeline() const
{
    return m_graphics_pipeline;
}

const vk::RenderPass&
RenderPass::renderPass() const
{
    return m_render_pass.get();
}

bool
RenderPass::createRenderPass(vk::Format swap_chain_format)
{
    vk::AttachmentDescription colorAttachment = {};
    colorAttachment.flags          = vk::AttachmentDescriptionFlags();
    colorAttachment.format         = swap_chain_format;
    colorAttachment.samples        = vk::SampleCountFlagBits::e1;
    colorAttachment.loadOp         = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp        = vk::AttachmentStoreOp::eStore;
    colorAttachment.stencilLoadOp  = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout  = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout    = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment              = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::SubpassDescription subpass = {};
    subpass.flags                  = vk::SubpassDescriptionFlags();
    subpass.pipelineBindPoint      = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount   = 1;
    subpass.pColorAttachments      = &colorAttachmentRef;

    vk::RenderPassCreateInfo renderpassInfo = {};
    renderpassInfo.flags                    = vk::RenderPassCreateFlags();
    renderpassInfo.attachmentCount          = 1;
    renderpassInfo.pAttachments             = &colorAttachment;
    renderpassInfo.subpassCount             = 1;
    renderpassInfo.pSubpasses               = &subpass;

    try
    {
        m_render_pass = LOGICAL_DEVICE.createRenderPassUnique(renderpassInfo);
    }
    catch (vk::SystemError err)
    {
        return false;
    }
    return true;
}

bool
RenderPass::create(const vk::PipelineLayout& pipeline_layout,
                   vk::Format swap_chain_format,
                   const vk::Extent2D& extent)
{
    if (!createRenderPass(swap_chain_format)) return false;

    PipelineConfigInfo pipeline_config_info = {extent};

    if (!m_graphics_pipeline.create<VertexDescription>(
            pipeline_config_info, pipeline_layout, m_render_pass.get()))
        return false;

    return true;
}
}; // namespace kusengine
