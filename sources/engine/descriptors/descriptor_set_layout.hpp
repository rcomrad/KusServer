#ifndef DESCRIPTOR_SET_LAYOUT_HPP
#define DESCRIPTOR_SET_LAYOUT_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

namespace kusengine
{
struct DescriptorBindingData
{
    int index;
    vk::DescriptorType type;
    int count;
    vk::ShaderStageFlags stage;
};

class DescriptorSetLayout
{
public:
    void create(const std::vector<DescriptorBindingData>& data);

    uint32_t count() const;

    const vk::DescriptorSetLayout& descriptorSetLayout() const;

private:
    uint32_t m_count;

    vk::UniqueDescriptorSetLayout m_descriptor_set_layout;
};

}; // namespace kusengine

#endif // DESCRIPTOR_SET_LAYOUT_HPP
