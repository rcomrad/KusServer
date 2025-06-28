#include "descriptor_manager.hpp"

namespace kusengine::render
{

void
DescriptorManager::addAllocator(
    const std::string& key,
    const std::vector<DescriptorBindingData>& binding_data)
{
    m_descriptor_allocator_storage[key].init(binding_data);
}

const DescriptorAllocator&
DescriptorManager::getAllocator(const std::string& key) const& noexcept
{
    return m_descriptor_allocator_storage.at(key);
}

void
DescriptorManager::setup()
{
    setupDefaultBindingsData();
}

void
DescriptorManager::setupDefaultBindingsData()
{
    std::vector<DescriptorBindingData> default_vertex_shader_bindings_data(2);
    default_vertex_shader_bindings_data[0].count         = 1;
    default_vertex_shader_bindings_data[0].binding_index = 0;
    default_vertex_shader_bindings_data[0].stage =
        vk::ShaderStageFlagBits::eVertex;
    default_vertex_shader_bindings_data[0].type =
        vk::DescriptorType::eUniformBuffer;

    default_vertex_shader_bindings_data[1].count         = 1;
    default_vertex_shader_bindings_data[1].binding_index = 1;
    default_vertex_shader_bindings_data[1].stage =
        vk::ShaderStageFlagBits::eVertex;
    default_vertex_shader_bindings_data[1].type =
        vk::DescriptorType::eStorageBuffer;

    addAllocator("default_vertex_shader", default_vertex_shader_bindings_data);

    std::vector<DescriptorBindingData> default_fragment_shader_bindings_data(1);
    default_fragment_shader_bindings_data[0].count         = 1;
    default_fragment_shader_bindings_data[0].binding_index = 0;
    default_fragment_shader_bindings_data[0].stage =
        vk::ShaderStageFlagBits::eFragment;
    default_fragment_shader_bindings_data[0].type =
        vk::DescriptorType::eCombinedImageSampler;

    addAllocator("default_fragment_shader",
                 default_fragment_shader_bindings_data);
}

void
DescriptorManager::translateDescriptorDataToFrame(SwapChainFrame& frame) const
{
    frame.createDescriptorSet(
        m_descriptor_allocator_storage.at("default_vertex_shader"));
}
// void
// DescriptorManager::init(
//     const std::vector<std::vector<DescriptorBindingData>>& bindings)
// {
//     for (int i = 0; i < bindings.size(); ++i)
//     {
//         addDescriptorConstruct(bindings[0]);
//         m_vk_layouts.emplace_back(
//             m_descriptor_constructors[i].layout.descriptorSetLayout());
//     }
// }

}; // namespace kusengine::render
