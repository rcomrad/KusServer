#include "resource_storage.hpp"

namespace kusengine::render
{

ResourceStorage::ResourceStorage(const DescriptorManager& desc_manager,
                                 DescriptorSetLayoutType dslt)
    : m_descriptor_set_layout_type(dslt),
      m_layout(desc_manager.getAllocator(dslt).layout())
{
    m_descriptor_sets.resize(1);
    desc_manager.getAllocator(dslt).allocate(m_descriptor_sets[0]);
}

void
ResourceStorage::bind(const vk::CommandBuffer& cmd,
                      const vk::PipelineLayout& pipelayout) const noexcept
{
    cmd.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelayout, 0u,
                           m_descriptor_sets.size(), m_descriptor_sets.data(),
                           0, nullptr);
}

} // namespace kusengine::render
