#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

namespace kusengine
{
App::App()
{

    WindowCreateInfo window_info;
    window_info.width  = WIDTH;
    window_info.height = HEIGHT;
    window_info.title  = "Simple app window";

    m_window.initWindow(window_info);
    m_device.initDevice(m_window);
    loadModels();
    createPipelineLayout();
    m_swap_chain.initSwapChain(&m_device, m_window.getExtent());
    createPipeline();
    createCommandBuffers();
}

App::~App()
{
    vkDestroyPipelineLayout(m_device.device(), m_pipeline_layout, nullptr);
}

void
App::generateTrinagle(std::vector<Model::Vertex>& verteces,
                      const Model::Vertex& A,
                      const Model::Vertex& B,
                      const Model::Vertex& C,
                      int depth)
{
    if (depth == 0)
    {
        verteces.emplace_back(A);
        verteces.emplace_back(B);
        verteces.emplace_back(C);
        return;
    }

    Model::Vertex D = {
        {(A.position.x + B.position.x) / 2, (A.position.y + B.position.y) / 2}
    };
    Model::Vertex E = {
        {(A.position.x + C.position.x) / 2, (A.position.y + C.position.y) / 2}
    };
    Model::Vertex F = {
        {(C.position.x + B.position.x) / 2, (C.position.y + B.position.y) / 2}
    };

    generateTrinagle(verteces, A, E, D, depth - 1);
    generateTrinagle(verteces, B, D, F, depth - 1);
    generateTrinagle(verteces, C, E, F, depth - 1);
}

void
App::loadModels()
{
    std::vector<Model::Vertex> start_vertices = {
        {{0.0, -0.5}}, {{0.5, 0.5}}, {{-0.5, 0.5}}};
    std::vector<Model::Vertex> vertices;

    generateTrinagle(vertices, start_vertices[0], start_vertices[1],
                     start_vertices[2], 6);

    m_model_ptr = std::make_unique<Model>(&m_device, vertices);
}

void
App::createPipelineLayout()
{
    VkPipelineLayoutCreateInfo layout_info{};
    layout_info.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layout_info.setLayoutCount = 0;
    layout_info.pSetLayouts    = nullptr;
    layout_info.pushConstantRangeCount = 0;
    layout_info.pPushConstantRanges    = nullptr;

    vkCreatePipelineLayout(m_device.device(), &layout_info, 0,
                           &m_pipeline_layout);
}

void
App::createPipeline()
{
    auto default_pipeline_config_info = Pipeline::defaultPipelineConfigInfo(
        m_swap_chain.width(), m_swap_chain.height());

    default_pipeline_config_info.render_pass     = m_swap_chain.getRenderPass();
    default_pipeline_config_info.pipeline_layout = m_pipeline_layout;

    m_pipeline_ptr = std::make_unique<Pipeline>();
    m_pipeline_ptr->initPipeline(
        "sources/engine/shaders/vertex_shader.vert.spv",
        "sources/engine/shaders/fragment_shader.frag.spv", &m_device,
        default_pipeline_config_info);
}

void
App::run()
{
    while (m_window.isOpen())
    {
        m_window.handleEvents();
        drawFrame();
    }
    vkDeviceWaitIdle(m_device.device());
}

void
App::createCommandBuffers()
{
    m_command_buffer_vector.resize(m_swap_chain.imageCount());

    VkCommandBufferAllocateInfo buffer_alloc_info{};
    buffer_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    buffer_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    buffer_alloc_info.commandPool = m_device.getCommandPool();
    buffer_alloc_info.commandBufferCount =
        static_cast<uint32_t>(m_command_buffer_vector.size());

    vkAllocateCommandBuffers(m_device.device(), &buffer_alloc_info,
                             m_command_buffer_vector.data());

    for (int i = 0; i < m_command_buffer_vector.size(); ++i)
    {
        VkCommandBufferBeginInfo buffer_begin_info{};
        buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkBeginCommandBuffer(m_command_buffer_vector[i], &buffer_begin_info);

        VkRenderPassBeginInfo renderpass_begin_info{};
        renderpass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderpass_begin_info.renderPass  = m_swap_chain.getRenderPass();
        renderpass_begin_info.framebuffer = m_swap_chain.getFrameBuffer(i);
        renderpass_begin_info.renderArea.offset = {0, 0};
        renderpass_begin_info.renderArea.extent =
            m_swap_chain.getSwapChainExtent();

        VkClearValue clear_value{};
        clear_value.color = {0.1, 0.1, 0.1, 1.0};

        renderpass_begin_info.clearValueCount = 1u;
        renderpass_begin_info.pClearValues    = &clear_value;

        vkCmdBeginRenderPass(m_command_buffer_vector[i], &renderpass_begin_info,
                             VK_SUBPASS_CONTENTS_INLINE);

        m_pipeline_ptr->bind(m_command_buffer_vector[i]);
        m_model_ptr->bind(m_command_buffer_vector[i]);
        m_model_ptr->draw(m_command_buffer_vector[i]);
        // vkCmdDraw(m_command_buffer_vector[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(m_command_buffer_vector[i]);

        vkEndCommandBuffer(m_command_buffer_vector[i]);
    }
}

void
App::drawFrame()
{
    // uint32_t image_index;

    // m_swap_chain.acquireNextImage(&image_index);

    // m_swap_chain.submitCommandBuffers(m_command_buffer_vector.data(),
    //                                   &image_index);

    uint32_t image_index;

    m_swap_chain.acquireNextImage(&image_index);

    m_swap_chain.submitCommandBuffers(m_command_buffer_vector, &image_index);

    // This call will signal the Fence when the GPU Work is done
}
}; // namespace kusengine
