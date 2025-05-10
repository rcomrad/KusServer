#include "descriptor_manager.hpp"

namespace kusengine
{

const std::vector<vk::DescriptorSetLayout>&
DescriptorManager::descriptorSetLayoutVector() const
{
    return m_vk_layouts;
}

const std::vector<DescriptorManager::DescriptorConstruct>&
DescriptorManager::descriptorConstructs() const
{
    return m_descriptor_constructors;
}

void
DescriptorManager::addDescriptorConstruct(
    const std::vector<DescriptorBindingData>& binding_data)
{
    DescriptorConstruct construct;
    construct.layout.create(binding_data);
    construct.pool.create(binding_data, 100, 100);
    m_descriptor_constructors.emplace_back(std::move(construct));
}

void
DescriptorManager::create()
{
    std::vector<DescriptorBindingData> bindings;

    // First Layout
    DescriptorBindingData binding_data;
    binding_data.index = 0;
    binding_data.stage = vk::ShaderStageFlagBits::eVertex;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eUniformBuffer;
    bindings.emplace_back(binding_data);

    binding_data.index = 1;
    binding_data.stage = vk::ShaderStageFlagBits::eVertex;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eStorageBuffer;
    bindings.emplace_back(binding_data);

    addDescriptorConstruct(bindings);

    // Second Layout
    bindings.clear();
    binding_data.index = 0;
    binding_data.stage = vk::ShaderStageFlagBits::eFragment;
    binding_data.count = 1;
    binding_data.type  = vk::DescriptorType::eCombinedImageSampler;
    bindings.emplace_back(binding_data);

    addDescriptorConstruct(bindings);

    for (int i = 0; i < m_descriptor_constructors.size(); ++i)
    {
        m_vk_layouts.emplace_back(
            m_descriptor_constructors[i].layout.descriptorSetLayout());
    }
}
}; // namespace kusengine
