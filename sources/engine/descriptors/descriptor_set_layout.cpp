#include "descriptor_set_layout.hpp"

#include <iostream>

#include "engine/device/device.hpp"

namespace kusengine
{
void
DescriptorSetLayout::create(const DescriptorSetLayoutData& data)
{
    std::vector<vk::DescriptorSetLayoutBinding> layout_bindings;
    layout_bindings.reserve(data.count);

    for (int i = 0; i < data.count; i++)
    {
        vk::DescriptorSetLayoutBinding layout_binding;
        layout_binding.binding         = data.indices[i];
        layout_binding.descriptorType  = data.types[i];
        layout_binding.descriptorCount = data.counts[i];
        layout_binding.stageFlags      = data.stages[i];
        layout_bindings.emplace_back(layout_binding);
    }

    vk::DescriptorSetLayoutCreateInfo layout_info;
    layout_info.flags        = vk::DescriptorSetLayoutCreateFlagBits();
    layout_info.bindingCount = data.count;
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

const vk::DescriptorSetLayout&
DescriptorSetLayout::descriptorSetLayout() const
{
    return m_descriptor_set_layout.get();
}
}; // namespace kusengine
