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
    std::vector<DescriptorBindingData> bindings;

    DescriptorBindingData binding_data;
    binding_data.index = 0;
    binding_data.stage = vk::ShaderStageFlagBits::eVertex;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eUniformBuffer;

    bindings.emplace_back(binding_data);

    //
    binding_data.index = 1;
    binding_data.stage = vk::ShaderStageFlagBits::eVertex;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eStorageBuffer;

    bindings.emplace_back(binding_data);

    m_layout.create(bindings);

    m_desc_pool.create(bindings, 10, 3);
}
}; // namespace kusengine
