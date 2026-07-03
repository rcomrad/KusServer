#pragma once

#include <vulkan/vulkan.hpp>

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/buffers/staging_buffer.hpp"

#include "raw_texture.hpp"
#include "sprite_push_data.hpp"

namespace gpu::sprite
{

struct Sprite
{
    Sprite(logic::Device& a_device,
           vk::DescriptorSetLayout a_desc_set_layout,
           vk::DescriptorPool m_descriptor_pool,
           RawTexture& a_texture);

    void resize(uint32_t a_win_height, uint32_t a_win_width);

    void draw(vk::PipelineLayout a_pipeline_layout,
              command::BaseCommand& a_cmd,
              SpritePushData& a_push);

private:
    static vk::UniqueImageView createImageView(logic::Device& a_device,
                                               vk::Image a_image);
    static vk::UniqueSampler createSampler(logic::Device& a_device);
    static vk::DescriptorSet createDescriptorSet(
        logic::Device& a_device,
        vk::DescriptorSetLayout a_desc_set_layout,
        vk::DescriptorPool m_descriptor_pool);
    static void updateDescriptorSet(logic::Device& a_device,
                                    vk::ImageView a_view,
                                    vk::Sampler a_sampler,
                                    vk::DescriptorSet a_desc_set);

    vk::UniqueImage m_image;
    vk::UniqueImageView m_view;
    vk::UniqueSampler m_sampler;
    vk::DescriptorSet m_descriptor_set; // pool manages free

    uint32_t m_height;
    uint32_t m_width;

    float m_scaler_x;
    float m_scaler_y;
};

} // namespace gpu::sprite
