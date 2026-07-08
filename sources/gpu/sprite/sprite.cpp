#include "sprite.hpp"

#include "gpu/command/base_command.hpp"
#include "gpu/logic/device.hpp"

#include "raw_texture.hpp"
#include "sprite_push_data.hpp"
#include "texture_info.hpp"

gpu::sprite::Sprite::Sprite(logic::Device& a_device,
                            vk::DescriptorSetLayout a_desc_set_layout,
                            vk::DescriptorPool a_descriptor_pool,
                            RawTexture& a_texture,
                            const TextureInfo& a_info)
    : Position(a_texture, a_info), Animation(a_info)
{
    m_image   = std::move(a_texture.obtainImage());
    m_view    = createImageView(a_device, *m_image);
    m_sampler = createSampler(a_device);
    m_descriptor_set =
        createDescriptorSet(a_device, a_desc_set_layout, a_descriptor_pool);

    updateDescriptorSet(a_device, *m_view, *m_sampler, m_descriptor_set);
}

void
gpu::sprite::Sprite::draw(vk::PipelineLayout a_pipeline_layout,
                          command::BaseCommand& a_cmd,
                          SpritePushData& a_push,
                          type::AnimationFrame a_frame_num) const
{

    a_cmd.bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                             a_pipeline_layout, 0, m_descriptor_set, {});
    drawPosition(a_push);
    drawAnimation(a_push, a_frame_num);
}

vk::UniqueImageView
gpu::sprite::Sprite::createImageView(logic::Device& a_device, vk::Image a_image)
{
    vk::ImageViewCreateInfo view_info;
    view_info.setImage(a_image)
        .setViewType(vk::ImageViewType::e2D)
        .setFormat(vk::Format::eR8G8B8A8Unorm)
        .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
    return a_device.createImageViewUnique(view_info);
}

vk::UniqueSampler
gpu::sprite::Sprite::createSampler(logic::Device& a_device)
{
    vk::SamplerCreateInfo sampler_info;
    sampler_info.setMinFilter(vk::Filter::eNearest)
        .setMagFilter(vk::Filter::eNearest);
    return a_device.createSamplerUnique(sampler_info);
}

vk::DescriptorSet
gpu::sprite::Sprite::createDescriptorSet(
    logic::Device& a_device,
    vk::DescriptorSetLayout a_desc_set_layout,
    vk::DescriptorPool m_descriptor_pool)
{

    vk::DescriptorSetAllocateInfo desc_set_alloc_info;
    desc_set_alloc_info.setPSetLayouts(&a_desc_set_layout)
        .setDescriptorSetCount(1)
        .setDescriptorPool(m_descriptor_pool);
    return a_device.allocateDescriptorSets(desc_set_alloc_info)[0];
}

void
gpu::sprite::Sprite::updateDescriptorSet(logic::Device& a_device,
                                         vk::ImageView a_view,
                                         vk::Sampler a_sampler,
                                         vk::DescriptorSet a_desc_set)
{
    std::vector<vk::DescriptorImageInfo> desc_img_info;
    desc_img_info.emplace_back()
        .setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal)
        .setImageView(a_view)
        .setSampler(a_sampler);

    std::vector<vk::WriteDescriptorSet> write_desc_set;
    write_desc_set.emplace_back()
        .setDstSet(a_desc_set)
        .setImageInfo(desc_img_info)
        .setDstBinding(0)
        .setDescriptorCount(1)
        .setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
    a_device.updateDescriptorSets(write_desc_set, {});
}
