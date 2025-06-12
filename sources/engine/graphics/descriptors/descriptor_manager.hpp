#ifndef DESCRIPTOR_MANAGER_HPP
#define DESCRIPTOR_MANAGER_HPP

#include <vulkan/vulkan.hpp>

#include <map>

#include "descriptor_pool.hpp"
#include "descriptor_set_layout.hpp"

namespace kusengine
{
class DescriptorManager
{
public:
    struct DescriptorConstruct
    {
        // const DescriptorPool& Pool() const;

        DescriptorSetLayout layout;
        DescriptorPool pool;
    };

    DescriptorManager() = default;

    void create();

    const std::vector<vk::DescriptorSetLayout>& descriptorSetLayoutVector()
        const;

    const std::vector<DescriptorConstruct>& descriptorConstructs() const;

private:
    void addDescriptorConstruct(
        const std::vector<DescriptorBindingData>& binding_data);

    std::vector<DescriptorConstruct> m_descriptor_constructors;

    std::vector<vk::DescriptorSetLayout> m_vk_layouts;
};
}; // namespace kusengine

#endif // DESCRIPTOR_MANAGER_HPP
