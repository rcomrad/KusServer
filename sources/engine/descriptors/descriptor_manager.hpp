#ifndef DESCRIPTOR_MANAGER_HPP
#define DESCRIPTOR_MANAGER_HPP

#include <vulkan/vulkan.hpp>

#include "descriptor_pool.hpp"
#include "descriptor_set_layout.hpp"

namespace kusengine
{
class DescriptorManager
{
public:
    DescriptorManager() = default;

    void create();

    const DescriptorSetLayout& descriptorSetLayout() const;
    const vk::DescriptorPool& descriptorPool() const;

private:
    DescriptorPool m_desc_pool;
    DescriptorSetLayout m_layout;
};
}; // namespace kusengine

#endif // DESCRIPTOR_MANAGER_HPP
