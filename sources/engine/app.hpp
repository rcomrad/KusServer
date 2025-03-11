#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include <vector>

#include "device.hpp"
#include "model.hpp"
#include "pipeline.hpp"
#include "swap_chain.hpp"
#include "window.hpp"

namespace kusengine
{
class App
{
public:
    App();
    ~App();

    void run();

    static constexpr int HEIGHT = 320;

    static constexpr int WIDTH = 500;

private:
    void loadModels();

    void createPipelineLayout();

    void createPipeline();

    void createCommandBuffers();

    void drawFrame();

    void generateTrinagle(std::vector<Model::Vertex>& verteces,
                          const Model::Vertex& A,
                          const Model::Vertex& B,
                          const Model::Vertex& C,
                          int depth);

    Device m_device;

    std::unique_ptr<Pipeline> m_pipeline_ptr;
    std::unique_ptr<Model> m_model_ptr;

    VkPipelineLayout m_pipeline_layout;

    std::vector<VkCommandBuffer> m_command_buffer_vector;

    SwapChain m_swap_chain;

    Window m_window;

    // Window m_window;
};
}; // namespace kusengine

#endif // APP_HPP
