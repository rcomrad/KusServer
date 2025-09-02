#ifndef RESOURCE_STORAGE_HPP
#define RESOURCE_STORAGE_HPP

#include <vector>

#include "engine/render_manager/buffers/storage_buffer.hpp"
#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/dynamics_data/uniform_buffer_object.hpp"

namespace kusengine::render
{

struct updBuffersDataArgs
{
    UBO* ubo;
    std::vector<char>* storage;

    // others
};

class ResourceStorage
{
public:
    virtual ~ResourceStorage() = default;

    void bind(const vk::CommandBuffer& cmd,
              const vk::PipelineLayout& pipelayout) const noexcept;

    virtual void updateBuffers(const updBuffersDataArgs& m_data) = 0;

    ResourceStorage(const DescriptorManager& desc_manager,
                    DescriptorSetLayoutType dslt);

protected:
    virtual void writeDescriptorSet() const noexcept = 0;

    DescriptorSetLayoutType m_descriptor_set_layout_type;

    vk::DescriptorSetLayout m_layout;

    std::vector<vk::DescriptorSet> m_descriptor_sets;
};
} // namespace kusengine::render

#endif // RESOURCE_STORAGE_HPP
