#ifndef BASIC_SCENE_HPP
#define BASIC_SCENE_HPP

#include "engine/render_manager/swap_chain/swap_chain_frame.hpp"
#include <vulkan/vulkan.hpp>
#include <string>

namespace kusengine::render
{
class BasicScene
{
public:
    virtual void create() = 0;

    void setSceneName(const std::string& new_scene_name);

    // void upd

    virtual void updMbddFrame(SwapChainFrame& frame) const = 0;

    virtual void bind(const vk::CommandBuffer& cmd) const = 0;

    virtual void draw(const vk::CommandBuffer& cmd,
                      const vk::PipelineLayout& layout) const = 0;

private:
    std::string m_scene_name;
};
}; // namespace kusengine::render

#endif // BASIC_SCENE_HPP
