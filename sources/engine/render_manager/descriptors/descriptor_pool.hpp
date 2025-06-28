#ifndef DESCRIPTOR_POOL_HPP
#define DESCRIPTOR_POOL_HPP

#include <vulkan/vulkan.hpp>

#include "descriptor_set_layout.hpp"

namespace kusengine
{
namespace render
{
class DescriptorPool
{
public:
    DescriptorPool() = default;

    void create(
        const std::vector<DescriptorBindingData>& descriptor_set_layout_data,
        uint32_t max_sets,
        uint32_t desc_count);

    const vk::DescriptorPool& descriptorPool() const;

private:
    vk::UniqueDescriptorPool m_descriptor_pool;
};
}; // namespace render
}; // namespace kusengine

#endif // DESCRIPTOR_POOL_HPP
