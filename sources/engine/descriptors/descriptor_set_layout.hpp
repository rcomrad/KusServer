#ifndef DESCRIPTOR_SET_LAYOUT_HPP
#define DESCRIPTOR_SET_LAYOUT_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

namespace kusengine
{
struct DescriptorSetLayoutData
{

    int count;
    std::vector<int> indices;
    std::vector<vk::DescriptorType> types;
    std::vector<int> counts;
    std::vector<vk::ShaderStageFlags> stages;
};

class DescriptorSetLayout
{
public:
    void create(const DescriptorSetLayoutData& data);

    uint32_t count() const;

    const vk::DescriptorSetLayout& descriptorSetLayout() const;

private:
    uint32_t m_count;

    vk::UniqueDescriptorSetLayout m_descriptor_set_layout;
};

}; // namespace kusengine

#endif // DESCRIPTOR_SET_LAYOUT_HPP
