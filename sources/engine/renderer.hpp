#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <mutex>

#include "device.hpp"
#include "model.hpp"
#include "pipeline.hpp"
#include "swap_chain.hpp"
#include "window.hpp"

namespace kusengine
{
class Renderer final
{
public:
    Renderer() = default;

    void render();

    void draw();

    void initRenderer(Window& window);

    void deviceWaitIdle();

private:
    //
    Window* m_window_ptr;

    //
    void compileShaders(const std::string& compile_program_path);

    void loadModels();

    void createPipelineLayout();

    void createPipeline();

    void createCommandBuffers();

    // void drawFrame();

    void recreateSwapChain();
    void recordCommandBuffer(int image_index);

    Device m_device;

    std::unique_ptr<Pipeline> m_pipeline_ptr;
    std::unique_ptr<Model> m_model_ptr;

    vk::UniquePipelineLayout m_pipeline_layout;

    std::vector<vk::CommandBuffer> m_command_buffer_vector;

    std::unique_ptr<SwapChain> m_swap_chain_ptr;
};
}; // namespace kusengine
#endif // RENDERER_HPP
