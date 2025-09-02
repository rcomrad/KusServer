#ifndef DESCRIPTOR_MANAGER_HPP
#define DESCRIPTOR_MANAGER_HPP

#include <vulkan/vulkan.hpp>

#include <string>
#include <unordered_map>

#include "engine/render_manager/shaders/shader_manager.hpp"
#include "engine/render_manager/swap_chain/swap_chain_frame.hpp"

#include "descriptor_allocator.hpp"

namespace kusengine::render
{

enum class DescriptorSetLayoutType
{
    UBO_x_STORAGE,
    COMBINED_IMAGE_SAMPLER
};

class DescriptorManager
{
public:
    void addAllocator(DescriptorSetLayoutType sh_type,
                      const std::vector<DescriptorBindingData>& binding_data);

    const DescriptorAllocator& getAllocator(DescriptorSetLayoutType sh_type) const& noexcept;

    void setup();

    void translateDescriptorDataToFrame(SwapChainFrame& frame) const;

private:
    void setupDefaultBindingsData();

    void addDescriptorConstruct(
        const std::vector<DescriptorBindingData>& binding_data);

    std::unordered_map<DescriptorSetLayoutType, DescriptorAllocator>
        m_descriptor_allocator_storage;
};

}; // namespace kusengine::render

#endif // DESCRIPTOR_MANAGER_HPP
