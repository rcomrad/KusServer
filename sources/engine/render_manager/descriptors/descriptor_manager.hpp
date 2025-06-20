#ifndef DESCRIPTOR_MANAGER_HPP
#define DESCRIPTOR_MANAGER_HPP

#include <vulkan/vulkan.hpp>

#include <map>

#include "descriptor_pool.hpp"
#include "descriptor_set_layout.hpp"

namespace kusengine
{
namespace render
{
class DescriptorManager
{
public:
    struct DescriptorConstruct
    {
        DescriptorSetLayout layout;
        DescriptorPool pool;
    };

    DescriptorManager() = default;

    void init(const std::vector<std::vector<DescriptorBindingData>>& bindings);

    const std::vector<vk::DescriptorSetLayout>& descriptorSetLayoutVector()
        const noexcept;

    const std::vector<DescriptorConstruct>& descriptorConstructs()
        const noexcept;

private:
    void addDescriptorConstruct(
        const std::vector<DescriptorBindingData>& binding_data);

    std::vector<DescriptorConstruct> m_descriptor_constructors;

    std::vector<vk::DescriptorSetLayout> m_vk_layouts;
};
}; // namespace render
}; // namespace kusengine

#endif // DESCRIPTOR_MANAGER_HPP
