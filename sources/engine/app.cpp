#define GLFW_INCLUDE_VULKAN

#include "app.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "utility/file_system/path_storage.hpp"

#include "engine_util.hpp"

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
    m_texture_storage.loadTextures(m_device);
    loadModels();
    {
        createDescriptorSetLayout();
        createSampler();
        createDescriptorPool();
        createDescriptorSet();
        updateDescriptorSet();
    }
    createPipelineLayout();
    recreateSwapChain();

    createCommandBuffers();

    m_target_frame_time = 1 / 150.0;
};

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

        // nA.color = triangle_color;
        // nB.color = triangle_color;
        // nC.color = triangle_color;

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
        {{0.0, -0.5}, {0.5, 0.0}},
        {{0.5, 0.5},  {0.0, 1.0}},
        {{-0.5, 0.5}, {1.0, 1.0}}
    };
    std::vector<Model::Vertex> vertices;

    vertices = start_vertices;

    // generateTrinagle(vertices, start_vertices[0], start_vertices[1],
    //                  start_vertices[2], 5);

    m_model_ptr = std::make_unique<Model>(&m_device, vertices);
}

void
App::createDescriptorSetLayout()
{
    std::vector<VkDescriptorSetLayoutBinding> layout_bindings = {
        engine_util::layout_binding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                    VK_SHADER_STAGE_FRAGMENT_BIT, 1, 0)};

    VkDescriptorSetLayoutCreateInfo layout_info = {};
    layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layout_info.bindingCount = layout_bindings.size();
    layout_info.pBindings    = layout_bindings.data();

    vkCreateDescriptorSetLayout(m_device.device(), &layout_info, 0,
                                &m_set_layout);
}

void
App::createSampler()
{
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType               = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.minFilter           = VK_FILTER_NEAREST;
    samplerInfo.magFilter           = VK_FILTER_NEAREST;

    vkCreateSampler(m_device.device(), &samplerInfo, 0, &m_sampler);
}

void
App::createDescriptorSet()
{
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType       = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pSetLayouts = &m_set_layout;
    allocInfo.descriptorSetCount = 1;
    allocInfo.descriptorPool     = m_descriptor_pool;
    vkAllocateDescriptorSets(m_device.device(), &allocInfo, &m_descriptor_set);
}

void
App::createDescriptorPool()
{
    std::vector<VkDescriptorPoolSize> poolSizes = {
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1},
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1}
    };

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.maxSets       = 1;
    poolInfo.poolSizeCount = poolSizes.size();
    poolInfo.pPoolSizes    = poolSizes.data();
    vkCreateDescriptorPool(m_device.device(), &poolInfo, 0, &m_descriptor_pool);
}

void
App::updateDescriptorSet()
{

    VkDescriptorImageInfo image_info{};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView   = m_texture_storage.view();
    image_info.sampler     = m_sampler;

    VkWriteDescriptorSet write{};
    write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet          = m_descriptor_set;
    write.pImageInfo      = &image_info;
    write.dstBinding      = 0;
    write.descriptorCount = 1;
    write.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

    vkUpdateDescriptorSets(m_device.device(), 1, &write, 0, 0);
}

void
App::createPipelineLayout()
{
    VkPipelineLayoutCreateInfo layout_info{};
    layout_info.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layout_info.setLayoutCount = 1;
    layout_info.pSetLayouts    = &m_set_layout;
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
    clear_value.color = {1.0, 1.0, 0.0, 1.0};

    renderpass_begin_info.clearValueCount = 1u;
    renderpass_begin_info.pClearValues    = &clear_value;

    vkCmdBeginRenderPass(m_command_buffer_vector[ind], &renderpass_begin_info,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindDescriptorSets(m_command_buffer_vector[ind],
                            VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout,
                            0, 1, &m_descriptor_set, 0, 0);

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
