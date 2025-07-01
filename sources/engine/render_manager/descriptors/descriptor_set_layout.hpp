#ifndef DESCRIPTOR_SET_LAYOUT_HPP
#define DESCRIPTOR_SET_LAYOUT_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

namespace kusengine
{

namespace render
{

struct DescriptorBindingData
{
    int binding_index;
    vk::DescriptorType type;
    int count;
    vk::ShaderStageFlags stage;
};

class DescriptorSetLayout
{
public:
    void create(const std::vector<DescriptorBindingData>& data);

    const vk::DescriptorSetLayout& descriptorSetLayout() const;

private:
    vk::UniqueDescriptorSetLayout m_descriptor_set_layout;
};
}; // namespace render
}; // namespace kusengine

#endif // DESCRIPTOR_SET_LAYOUT_HPP
