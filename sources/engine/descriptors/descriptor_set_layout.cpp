#include "descriptor_set_layout.hpp"

#include <iostream>

#include "engine/device/device.hpp"

namespace kusengine
{
void
DescriptorSetLayout::create(const DescriptorSetLayoutData& data)
{
    m_count = data.count;

    std::vector<vk::DescriptorSetLayoutBinding> layout_bindings;
    layout_bindings.reserve(m_count);

    for (int i = 0; i < m_count; i++)
    {
        vk::DescriptorSetLayoutBinding layout_binding;
        layout_binding.binding            = data.indices[i];
        layout_binding.descriptorType     = data.types[i];
        layout_binding.descriptorCount    = data.counts[i];
        layout_binding.stageFlags         = data.stages[i];
        layout_binding.pImmutableSamplers = nullptr;
        layout_bindings.push_back(layout_binding);
    }

    vk::DescriptorSetLayoutCreateInfo layout_info;
    layout_info.flags        = vk::DescriptorSetLayoutCreateFlagBits();
    layout_info.bindingCount = m_count;
    layout_info.pBindings    = layout_bindings.data();

    try
    {
        m_descriptor_set_layout =
            LOGICAL_DEVICE.createDescriptorSetLayoutUnique(layout_info);
    }
    catch (vk::SystemError err)
    {
        std::cerr << "Failed to create Descriptor set layout\n";
    }
}

uint32_t
DescriptorSetLayout::count() const
{
    return m_count;
}

const vk::DescriptorSetLayout&
DescriptorSetLayout::descriptorSetLayout() const
{
    return m_descriptor_set_layout.get();
}
}; // namespace kusengine
