#include "descriptor_pool.hpp"

#include <iostream>

#include "engine/graphics/device/device.hpp"

namespace kusengine
{

const vk::DescriptorPool&
DescriptorPool::descriptorPool() const
{
    return m_descriptor_pool.get();
}

void
DescriptorPool::create(
    const std::vector<DescriptorBindingData>& descriptor_set_layout_data,
    uint32_t max_sets,
    uint32_t desc_count)
{
    std::vector<vk::DescriptorPoolSize> poolSizes;

    for (int i = 0; i < descriptor_set_layout_data.size(); i++)
    {
        vk::DescriptorPoolSize poolSize;
        poolSize.type            = descriptor_set_layout_data[i].type;
        poolSize.descriptorCount = desc_count;
        poolSizes.push_back(poolSize);
    }

    vk::DescriptorPoolCreateInfo poolInfo;

    poolInfo.flags         = vk::DescriptorPoolCreateFlags();
    poolInfo.maxSets       = max_sets;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes    = poolSizes.data();

    try
    {
        m_descriptor_pool = LOGICAL_DEVICE.createDescriptorPoolUnique(poolInfo);
    }
    catch (vk::SystemError err)
    {
        std::cerr << err.what() << '\n';
    }
}
}; // namespace kusengine
