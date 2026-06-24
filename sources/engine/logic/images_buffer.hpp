#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include <vulkan/vulkan.hpp>

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include "engine/logic/device.hpp"

#include "base_buffer.hpp"
#include "command_pool.hpp"
#include "staging_buffer.hpp"

#define IMAGES_DIR "images"

namespace engine::logic
{

class ImagesBuffer
{
public:
    ImagesBuffer(logic::Device& a_device);

    // void bind(vk::UniqueCommandBuffer& a_commands);
    // void draw(vk::UniqueCommandBuffer& a_commands);

    void push(const std::filesystem::path& a_path);
    void collapse(logic::CommandPool& a_comm_pool,
                  logic::Queue& a_queue,
                  vk::DescriptorSetLayout a_desc_set_layout);

public:
    logic::Device& m_device;

    StagingBuffer m_transfer_buff;
    utils::LifecycleManager<BaseBuffer> m_memory;
    vk::UniqueDescriptorPool m_descriptor_pool;

    struct RawTexture
    {
        uint32_t height;
        uint32_t width;
        std::string name;
        vk::UniqueImage image;
        std::string dds_file;
        const char* file_data;
    };
    std::vector<RawTexture> m_prepared_data;

    struct Texture
    {
        vk::UniqueImage image;
        vk::UniqueImageView view;
        vk::UniqueSampler sampler;
        vk::DescriptorSet descriptor_set; // pool manages free
    };
    std::unordered_map<std::string, Texture> m_textures;
};

} // namespace engine::logic
