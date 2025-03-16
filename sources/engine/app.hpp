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

    static constexpr int HEIGHT = 520;

    static constexpr int WIDTH = 800;

private:
    void compileShaders(const std::string& compile_program_path);

    void loadModels();

    void createPipelineLayout();

    void createPipeline();

    void createCommandBuffers();

    void drawFrame();

    void recreateSwapChain();
    void recordCommandBuffer(int image_index);

    Device m_device;

    std::unique_ptr<Pipeline> m_pipeline_ptr;
    std::unique_ptr<Model> m_model_ptr;

    VkPipelineLayout m_pipeline_layout;

    std::vector<VkCommandBuffer> m_command_buffer_vector;

    std::unique_ptr<SwapChain> m_swap_chain_ptr;

    Window m_window;

    // Triangle
    void generateTrinagle(std::vector<Model::Vertex>& verteces,
                          const Model::Vertex& A,
                          const Model::Vertex& B,
                          const Model::Vertex& C,
                          int depth);

    void moveTriangle(float x, float y);

    // Time

    double getLoopTime();

    void FPSLimit(const double& loop_time);

    double m_target_frame_time;

    double m_last_time;

    // Window m_window;
};
}; // namespace kusengine

#endif // APP_HPP
