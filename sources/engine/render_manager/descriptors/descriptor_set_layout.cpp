#include "descriptor_set_layout.hpp"

#include <iostream>

#include "engine/render_manager/device/device.hpp"

namespace kusengine
{
namespace render
{
void
DescriptorSetLayout::create(const std::vector<DescriptorBindingData>& data)
{
    std::vector<vk::DescriptorSetLayoutBinding> layout_bindings;
    layout_bindings.reserve(data.size());

    for (int i = 0; i < data.size(); i++)
    {
        vk::DescriptorSetLayoutBinding layout_binding;
        layout_binding.binding            = data[i].binding_index;
        layout_binding.descriptorType     = data[i].type;
        layout_binding.descriptorCount    = data[i].count;
        layout_binding.stageFlags         = data[i].stage;
        layout_binding.pImmutableSamplers = nullptr;
        layout_bindings.emplace_back(layout_binding);
    }

    vk::DescriptorSetLayoutCreateInfo layout_info;
    layout_info.flags        = vk::DescriptorSetLayoutCreateFlagBits();
    layout_info.bindingCount = data.size();
    layout_info.pBindings    = layout_bindings.data();

    m_descriptor_set_layout =
        LOGICAL_DEVICE_INSTANCE.createDescriptorSetLayoutUnique(layout_info);
}

const vk::DescriptorSetLayout&
DescriptorSetLayout::descriptorSetLayout() const
{
    return m_descriptor_set_layout.get();
}
}; // namespace render
}; // namespace kusengine
