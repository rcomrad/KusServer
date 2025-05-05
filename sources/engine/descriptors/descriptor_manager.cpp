#include "descriptor_manager.hpp"

namespace kusengine
{

const DescriptorSetLayout&
DescriptorManager::descriptorSetLayout() const
{
    return m_layout;
}

const vk::DescriptorPool&
DescriptorManager::descriptorPool() const
{
    return m_desc_pool.descriptorPool();
}

void
DescriptorManager::create()
{
    DescriptorSetLayoutData bindings;
    bindings.count = 1;

    bindings.indices.push_back(0);
    bindings.types.push_back(vk::DescriptorType::eUniformBuffer);
    bindings.counts.push_back(1);
    bindings.stages.push_back(vk::ShaderStageFlagBits::eVertex);

    //
    // bindings.indices.push_back(1);
    // bindings.types.push_back(vk::DescriptorType::eStorageBuffer);
    // bindings.counts.push_back(1);
    // bindings.stages.push_back(vk::ShaderStageFlagBits::eVertex);

    m_layout.create(bindings);

    m_desc_pool.create(bindings, 10, 3);
}
}; // namespace kusengine
