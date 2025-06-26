#ifndef DESCRIPTOR_MANAGER_HPP
#define DESCRIPTOR_MANAGER_HPP

#include <vulkan/vulkan.hpp>

#include <string>
#include <unordered_map>

#include "descriptor_allocator.hpp"

namespace kusengine::render
{

class DescriptorManager
{
public:
    void addAllocator(const std::string& key,
                      const std::vector<DescriptorBindingData>& binding_data);

    const DescriptorAllocator& getAllocator(
        const std::string& key) const& noexcept;

    void setup();

private:
    void setupDefaultBindingsData();

    void addDescriptorConstruct(
        const std::vector<DescriptorBindingData>& binding_data);

    std::unordered_map<std::string, DescriptorAllocator>
        m_descriptor_allocator_storage;
};

}; // namespace kusengine::render

#endif // DESCRIPTOR_MANAGER_HPP
