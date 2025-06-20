#include "descriptor_manager.hpp"

namespace kusengine
{
namespace render
{
const std::vector<vk::DescriptorSetLayout>&
DescriptorManager::descriptorSetLayoutVector() const noexcept
{
    return m_vk_layouts;
}

const std::vector<DescriptorManager::DescriptorConstruct>&
DescriptorManager::descriptorConstructs() const noexcept
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
DescriptorManager::init(
    const std::vector<std::vector<DescriptorBindingData>>& bindings)
{
    for (int i = 0; i < bindings.size(); ++i)
    {
        addDescriptorConstruct(bindings[0]);
        m_vk_layouts.emplace_back(
            m_descriptor_constructors[i].layout.descriptorSetLayout());
    }
}
}; // namespace render
}; // namespace kusengine
