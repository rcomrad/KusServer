#pragma once

#include <vulkan/vulkan.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#include "gpu/utils/typedef.hpp"

#include "animation.hpp"
#include "position.hpp"
#include "raw_texture.hpp"
#include "sprite_push_data.hpp"
#include "texture_info.hpp"

namespace gpu::sprite
{

class Sprite : public Position, public Animation
{
public:
    Sprite(logic::Device& a_device,
           vk::DescriptorSetLayout a_desc_set_layout,
           vk::DescriptorPool m_descriptor_pool,
           RawTexture& a_texture,
           const TextureInfo& a_info);

    void draw(vk::PipelineLayout a_pipeline_layout,
              command::BaseCommand& a_cmd,
              SpritePushData& a_push,
              type::AnimationFrame a_frame_num);

private:
    vk::UniqueImage m_image;
    vk::UniqueImageView m_view;
    vk::UniqueSampler m_sampler;
    vk::DescriptorSet m_descriptor_set; // pool manages free

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
};

} // namespace gpu::sprite
