#include "descriptor_allocator.hpp"

#include "engine/render_manager/device/device.hpp"
namespace kusengine::render
{

void
DescriptorAllocator::init(const std::vector<DescriptorBindingData>& bindings)
{
    m_layout.create(bindings);
    m_pool.create(bindings, 100, 100);
}

const vk::DescriptorSetLayout&
DescriptorAllocator::layout() const& noexcept
{
    return m_layout.descriptorSetLayout();
}

void
DescriptorAllocator::allocate(vk::UniqueDescriptorSet& set) const
{
    vk::DescriptorSetAllocateInfo allocInfo(m_pool.descriptorPool(), 1,
                                            &m_layout.descriptorSetLayout());

    set = std::move(
        LOGICAL_DEVICE_INSTANCE.allocateDescriptorSetsUnique(allocInfo)[0]);
}

void
DescriptorAllocator::allocate(vk::DescriptorSet& set) const
{
    vk::DescriptorSetAllocateInfo allocInfo(m_pool.descriptorPool(), 1,
                                            &m_layout.descriptorSetLayout());

    set = LOGICAL_DEVICE_INSTANCE.allocateDescriptorSets(allocInfo)[0];
}

} // namespace kusengine::render
