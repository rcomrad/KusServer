#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include <memory>
#include <vector>

#include "gpu/command/base_command.hpp"

#include "graphic_pipeline.hpp"
#include "image_collection.hpp"
#include "render_pass.hpp"
#include "shader.hpp"
#include "swap_chain.hpp"

namespace gpu::pipeline
{

class Manager
{
public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void reset();
    void bindToNextImage(int a_image_num, command::BaseCommand& a_cmd_buff);

    inline auto getLayout()
    {
        return m_graphics_pipeline->getLayout();
    }

    inline auto getDescSetLayout()
    {
        return m_graphics_pipeline->getDescSetLayout();
    }

private:
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    utils::LifecycleManager<SwapChain> m_swap_chain;
    utils::LifecycleManager<RenderPass> m_render_pass;
    utils::LifecycleManager<ImageCollection> m_image_collection;
    std::vector<vk::UniqueShaderModule> m_shaiders;
    utils::LifecycleManager<GraphicsPipeline> m_graphics_pipeline;

    void createShaider(std::string_view a_name);
};

} // namespace gpu::pipeline
