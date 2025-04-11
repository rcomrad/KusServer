#include "renderer.hpp"

#include "utility/file_system/path_storage.hpp"
namespace kusengine
{

void
OLDRenderer::initRenderer(Window& window)
{
    m_instance.initInstance("engine start");
    //
    m_window_ptr = &window;
    compileShaders("glslc.exe");
    m_device.initDevice(window);
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
    createCommandBuffers();
}

void
OLDRenderer::deviceWaitIdle()
{
    m_device.device().waitIdle();
}

void
OLDRenderer::draw()
{
    uint32_t image_index;

    auto result = m_swap_chain_ptr->acquireNextImage(&image_index);

    if (result == vk::Result::eErrorOutOfDateKHR)
    {
        recreateSwapChain();
        return;
    }

    recordCommandBuffer(image_index);

    result = m_swap_chain_ptr->submitCommandBuffers(
        {m_command_buffer_vector[image_index]}, &image_index);

    if (result == vk::Result::eErrorOutOfDateKHR ||
        result == vk::Result::eSuboptimalKHR ||
        m_window_ptr->wasWindowResized())
    {
        m_window_ptr->resetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
}

void
OLDRenderer::compileShaders(const std::string& compile_program_path)
{
    auto sources_path = util::PathStorage::getFolderPath("sources");

    if (!sources_path.has_value())
    {
        throw std::exception("Did not find sources folder");
    }

    std::string vertex_shader_path = sources_path.value().data();
    vertex_shader_path += "engine/shaders/vertex_shader.vert";

    std::string fragment_shader_path = sources_path.value().data();
    fragment_shader_path += "engine/shaders/fragment_shader.frag";

    std::string vertex_compile_command;
    std::string fragment_compile_command;

#ifdef _WIN32
    vertex_compile_command = compile_program_path + " " + vertex_shader_path +
                             " -o " + vertex_shader_path + ".spv";
    fragment_compile_command = compile_program_path + " " +
                               fragment_shader_path + " -o " +
                               fragment_shader_path + ".spv";
#else

#endif // _WIN32

    system(vertex_compile_command.c_str());
    system(fragment_compile_command.c_str());
}

void
OLDRenderer::loadModels()
{
    std::vector<Model::Vertex> start_vertices = {
        {{-0.5f + 0.4, -0.5f + 0.4}, {0.0f, 0.0f}, 0},
        {{0.5f + 0.4, -0.5f + 0.4},  {1.0f, 0.0f}, 0},
        {{0.5f + 0.4, 0.5f + 0.4},   {1.0f, 1.0f}, 0},
        {{-0.5f + 0.4, 0.5f + 0.4},  {0.0f, 1.0f}, 0},
        //
        {{-0.5f - 0.4, -0.5f - 0.4}, {0.0f, 0.0f}, 1},
        {{0.5f - 0.4, -0.5f - 0.4},  {1.0f, 0.0f}, 1},
        {{0.5f - 0.4, 0.5f - 0.4},   {1.0f, 1.0f}, 1},
        {{-0.5f - 0.4, 0.5f - 0.4},  {0.0f, 1.0f}, 1}
    };
    const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

    std::vector<Model::Vertex> vertices;

    vertices = start_vertices;

    // generateTrinagle(vertices, start_vertices[0], start_vertices[1],
    //                  start_vertices[2], 3);

    m_model_ptr = std::make_unique<Model>(&m_device, start_vertices, indices);
}

void
OLDRenderer::createPipelineLayout()
{
    vk::PipelineLayoutCreateInfo layout_info(
        vk::PipelineLayoutCreateFlags(),      // flags
        1,                                    // setLayoutCount
        m_model_ptr->getSetLayoutsConstPtr(), // pSetLayouts
        0,                                    // pushConstantRangeCount
        nullptr                               // pPushConstantRanges
    );

    m_pipeline_layout.get() =
        m_device.device().createPipelineLayout(layout_info);
}

void
OLDRenderer::createPipeline()
{
    PipelineConfigInfo default_pipeline_config_info =
        Pipeline::defaultPipelineConfigInfo(m_swap_chain_ptr->width(),
                                            m_swap_chain_ptr->height());

    default_pipeline_config_info.render_pass =
        m_swap_chain_ptr->getRenderPass();

    default_pipeline_config_info.pipeline_layout = m_pipeline_layout.get();

    m_pipeline_ptr = std::make_unique<Pipeline>();

    std::string app_path =
        util::PathStorage::getFolderPath("app").value().data();

    m_pipeline_ptr->initPipeline(
        app_path + "sources/engine/shaders/vertex_shader.vert.spv",
        app_path + "sources/engine/shaders/fragment_shader.frag.spv", &m_device,
        default_pipeline_config_info);
}

void
OLDRenderer::createCommandBuffers()
{
    m_command_buffer_vector.resize(m_swap_chain_ptr->imageCount());

    vk::CommandBufferAllocateInfo buffer_alloc_info(
        m_device.getCommandPool(),        // commandPool
        vk::CommandBufferLevel::ePrimary, // level
        static_cast<uint32_t>(
            m_command_buffer_vector.size()) // commandBufferCount
    );

    m_command_buffer_vector =
        m_device.device().allocateCommandBuffers(buffer_alloc_info);
}

void
OLDRenderer::recordCommandBuffer(int ind)
{
    vk::CommandBufferBeginInfo buffer_begin_info{};
    m_command_buffer_vector[ind].begin(buffer_begin_info);

    // Set up render pass
    vk::ClearValue clear_value(
        vk::ClearColorValue(std::array<float, 4>{1.0f, 1.0f, 0.0f, 1.0f}));

    vk::RenderPassBeginInfo renderpass_begin_info(
        m_swap_chain_ptr->getRenderPass(),
        m_swap_chain_ptr->getFrameBuffer(ind),
        vk::Rect2D({0, 0}, m_swap_chain_ptr->getSwapChainExtent()), 1,
        &clear_value);

    // Set viewport and scissor
    {
        vk::Viewport viewport(
            0.0f, 0.0f,
            static_cast<float>(m_swap_chain_ptr->getSwapChainExtent().width),
            static_cast<float>(m_swap_chain_ptr->getSwapChainExtent().height),
            0.0f, 1.0f);

        vk::Rect2D scissor({0, 0}, m_swap_chain_ptr->getSwapChainExtent());

        m_command_buffer_vector[ind].setViewport(0, 1, &viewport);
        m_command_buffer_vector[ind].setScissor(0, 1, &scissor);
    }

    // Begin render pass and draw commands
    m_command_buffer_vector[ind].beginRenderPass(renderpass_begin_info,
                                                 vk::SubpassContents::eInline);

    m_pipeline_ptr->bind(m_command_buffer_vector[ind]);
    m_model_ptr->bindDescriptorSets(m_command_buffer_vector[ind],
                                    m_pipeline_layout.get());
    m_model_ptr->bindVertexBuffer(m_command_buffer_vector[ind]);
    m_model_ptr->bindIndexBuffer(m_command_buffer_vector[ind]);

    m_model_ptr->draw(m_command_buffer_vector[ind]);

    // End commands
    m_command_buffer_vector[ind].endRenderPass();
    m_command_buffer_vector[ind].end();
}

void
OLDRenderer::recreateSwapChain()
{
    auto extent = m_window_ptr->getExtent();

    while (extent.height == 0 || extent.width == 0)
    {
        extent = m_window_ptr->getExtent();
        glfwWaitEvents();
    }
    deviceWaitIdle();
    m_swap_chain_ptr = std::make_unique<OLDSwapChain>(&m_device, extent);
    createPipeline();
}

}; // namespace kusengine
