#include "descriptor_set_layout.hpp"

#include <iostream>

#include "engine/graphics/device/device.hpp"

namespace kusengine
{
void
DescriptorSetLayout::create(const std::vector<DescriptorBindingData>& data)
{
    std::vector<vk::DescriptorSetLayoutBinding> layout_bindings;
    layout_bindings.reserve(data.size());

    for (int i = 0; i < data.size(); i++)
    {
        vk::DescriptorSetLayoutBinding layout_binding;
        layout_binding.binding            = data[i].index;
        layout_binding.descriptorType     = data[i].type;
        layout_binding.descriptorCount    = data[i].count;
        layout_binding.stageFlags         = data[i].stage;
        layout_binding.pImmutableSamplers = nullptr;
        layout_bindings.push_back(layout_binding);
    }

    vk::DescriptorSetLayoutCreateInfo layout_info;
    layout_info.flags        = vk::DescriptorSetLayoutCreateFlagBits();
    layout_info.bindingCount = data.size();
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
