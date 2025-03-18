#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "utility/file_system/path_storage.hpp"

namespace kusengine
{

void
App::initApp()
{
    WindowCreateInfo window_info;
    window_info.width  = WIDTH;
    window_info.height = HEIGHT;
    window_info.title  = "Simple app window";

    compileShaders("glslc.exe");

    m_window.initWindow(window_info);
    m_device.initDevice(m_window);
    loadModels();
    createPipelineLayout();
    recreateSwapChain();

    createCommandBuffers();

    m_target_frame_time = 1 / 150.0;
}

App::~App()
{
    vkDestroyPipelineLayout(m_device.device(), m_pipeline_layout, nullptr);
}

void
App::compileShaders(const std::string& compile_program_path)
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
App::generateTrinagle(std::vector<Model::Vertex>& verteces,
                      const Model::Vertex& A,
                      const Model::Vertex& B,
                      const Model::Vertex& C,
                      int depth)
{
    if (depth == 0)
    {
        glm::vec3 triangle_color = {(std::rand() % 255) / 255.f,
                                    (std::rand() % 255) / 255.f,
                                    (std::rand() % 255) / 255.f};
        Model::Vertex nA = A, nB = B, nC = C;

        nA.color = triangle_color;
        nB.color = triangle_color;
        nC.color = triangle_color;

        verteces.emplace_back(nA);
        verteces.emplace_back(nB);
        verteces.emplace_back(nC);
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
App::moveTriangle(float x, float y)
{
    m_model_ptr->move(x, y);
}

void
App::loadModels()
{
    std::vector<Model::Vertex> start_vertices = {
        {{0.0, -0.5}, {1.0, 1.0, 0.5}},
        {{0.5, 0.5},  {1.0, 1.0, 0.5}},
        {{-0.5, 0.5}, {1.0, 1.0, 0.5}}
    };
    std::vector<Model::Vertex> vertices;

    generateTrinagle(vertices, start_vertices[0], start_vertices[1],
                     start_vertices[2], 5);

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
        m_swap_chain_ptr->width(), m_swap_chain_ptr->height());

    default_pipeline_config_info.render_pass =
        m_swap_chain_ptr->getRenderPass();
    default_pipeline_config_info.pipeline_layout = m_pipeline_layout;

    m_pipeline_ptr = std::make_unique<Pipeline>();
    m_pipeline_ptr->initPipeline(
        "sources/engine/shaders/vertex_shader.vert.spv",
        "sources/engine/shaders/fragment_shader.frag.spv", &m_device,
        default_pipeline_config_info);
}

double
App::getLoopTime()
{
    double current_time = glfwGetTime();

    return current_time - std::exchange(m_last_time, current_time);
}

void
App::FPSLimit(const double& loop_time)
{
    if (loop_time < m_target_frame_time)
    {
        double sleep_time = m_target_frame_time - loop_time;
        glfwWaitEventsTimeout(sleep_time); // Ожидание
    }
}

bool
App::loopBody()
{
    m_window.handleEvents();

    auto key_codes = m_window.getKeyCodes();

    if (!m_window.isOpen())
    {
        vkDeviceWaitIdle(m_device.device());
        return false;
    }

    float x = 0, y = 0;

    double loop_time = getLoopTime();

    if (std::find(key_codes.begin(), key_codes.end(), GLFW_KEY_RIGHT) !=
        key_codes.end())
        x += 1.f * loop_time;

    if (std::find(key_codes.begin(), key_codes.end(), GLFW_KEY_LEFT) !=
        key_codes.end())
        x += -1.f * loop_time;
    if (std::find(key_codes.begin(), key_codes.end(), GLFW_KEY_DOWN) !=
        key_codes.end())
        y += 1.f * loop_time;
    if (std::find(key_codes.begin(), key_codes.end(), GLFW_KEY_UP) !=
        key_codes.end())
        y += -1.f * loop_time;

    moveTriangle(x, y);

    drawFrame();

    FPSLimit(loop_time);

    return true;
}

void
App::run()
{
    while (m_window.isOpen())
    {
        loopBody();
    }
    vkDeviceWaitIdle(m_device.device());
}

void
App::createCommandBuffers()
{
    m_command_buffer_vector.resize(m_swap_chain_ptr->imageCount());

    VkCommandBufferAllocateInfo buffer_alloc_info{};
    buffer_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    buffer_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    buffer_alloc_info.commandPool = m_device.getCommandPool();
    buffer_alloc_info.commandBufferCount =
        static_cast<uint32_t>(m_command_buffer_vector.size());

    vkAllocateCommandBuffers(m_device.device(), &buffer_alloc_info,
                             m_command_buffer_vector.data());
}

void
App::recordCommandBuffer(int ind)
{
    VkCommandBufferBeginInfo buffer_begin_info{};
    buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(m_command_buffer_vector[ind], &buffer_begin_info);

    VkRenderPassBeginInfo renderpass_begin_info{};
    renderpass_begin_info.sType      = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderpass_begin_info.renderPass = m_swap_chain_ptr->getRenderPass();
    renderpass_begin_info.framebuffer = m_swap_chain_ptr->getFrameBuffer(ind);
    renderpass_begin_info.renderArea.offset = {0, 0};
    renderpass_begin_info.renderArea.extent =
        m_swap_chain_ptr->getSwapChainExtent();

    VkClearValue clear_value{};
    clear_value.color = {0.0, 0.0, 0.0, 1.0};

    renderpass_begin_info.clearValueCount = 1u;
    renderpass_begin_info.pClearValues    = &clear_value;

    vkCmdBeginRenderPass(m_command_buffer_vector[ind], &renderpass_begin_info,
                         VK_SUBPASS_CONTENTS_INLINE);

    m_pipeline_ptr->bind(m_command_buffer_vector[ind]);
    m_model_ptr->bind(m_command_buffer_vector[ind]);
    m_model_ptr->draw(m_command_buffer_vector[ind]);

    vkCmdEndRenderPass(m_command_buffer_vector[ind]);

    vkEndCommandBuffer(m_command_buffer_vector[ind]);
}

void
App::recreateSwapChain()
{
    auto extent = m_window.getExtent();

    while (extent.height == 0 || extent.width == 0)
    {
        extent = m_window.getExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(m_device.device());
    m_swap_chain_ptr = std::make_unique<SwapChain>(&m_device, extent);
    createPipeline();
}

void
App::drawFrame()
{
    uint32_t image_index;

    auto result = m_swap_chain_ptr->acquireNextImage(&image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreateSwapChain();
        return;
    }

    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::exception("failed to acquire swap chain image!");
    }

    recordCommandBuffer(image_index);

    result = m_swap_chain_ptr->submitCommandBuffers(
        &m_command_buffer_vector[image_index], &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
        m_window.wasWindowResized())
    {
        m_window.resetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
    if (result != VK_SUCCESS)
    {
        throw std::exception("failed to present swap chain image!");
    }
}
}; // namespace kusengine
