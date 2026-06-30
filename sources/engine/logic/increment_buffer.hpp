// #pragma once

// #include <vulkan/vulkan.hpp>

// #include "engine/logic/device.hpp"

// #include "base_command.hpp"

// namespace engine::logic
// {

// class IncrementBuffer
// {
// public:
//     IncrementBuffer(logic::Device& a_device, vk::DeviceSize a_size);
//     ~IncrementBuffer();

//     void push(const char* a_data, vk::DeviceSize a_size);

//     void bind(logic::BaseCommand& a_commands);

// private:
//     logic::Device& m_device;
//     vk::DeviceSize m_size;
//     vk::DeviceSize m_cur_bound;

//     void* m_mapped_memory;
//     vk::UniqueBuffer m_buffer;
//     vk::UniqueDeviceMemory m_allocated_memory;

//     std::vector<vk::Buffer> m_buffers_for_bind;
//     std::vector<vk::DeviceSize> m_offsets_for_bind;

//     static vk::UniqueBuffer createBuffer(logic::Device& a_device,
//                                          vk::DeviceSize a_size,
//                                          vk::BufferUsageFlags a_usage);
//     static vk::UniqueDeviceMemory allocateMemory(
//         logic::Device& a_device,
//         vk::UniqueBuffer& a_buffer,
//         vk::MemoryPropertyFlags a_properties);
// };

// } // namespace engine::logic
