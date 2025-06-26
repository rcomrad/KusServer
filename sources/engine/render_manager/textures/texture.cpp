#include "texture.hpp"

#include "engine/render_manager/commands/command_buffer.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kusengine
{
namespace render
{
void
Texture::loadTexture(std::string_view file_path)
{
    int tex_channels;

    stbi_uc* pixels = stbi_load(file_path.data(), &m_width, &m_height,
                                &tex_channels, STBI_rgb_alpha);
    if (!pixels)
    {
        throw std::runtime_error(
            std::format("{}{}", "Failed to load texture file: ", file_path));
    }
    vk::DeviceSize imageSize = m_width * m_height * 4;

    StagingBuffer staging_buffer;
    staging_buffer.setData(pixels, imageSize);
    stbi_image_free(pixels);

    m_image.create(m_width, m_height);

    CommandBuffer command_buffer;
    command_buffer.create();
    auto queue = DEVICE_INSTANCE.getQueue("graphics");

    Buffer::copyBufferToImage(&staging_buffer, m_image, queue,
                              command_buffer.commandBuffer(), m_width,
                              m_height);

    // Отправка команд
    vk::SubmitInfo submitInfo(0, nullptr, nullptr, 1,
                              &(command_buffer.commandBuffer()));

    queue.submit(1, &submitInfo, nullptr);
    queue.waitIdle();

    m_image.createImageView();

    // Sampler
    vk::SamplerCreateInfo samplerInfo({},                              //
                                      vk::Filter::eLinear,             //
                                      vk::Filter::eLinear,             //
                                      vk::SamplerMipmapMode::eLinear,  //
                                      vk::SamplerAddressMode::eRepeat, //
                                      vk::SamplerAddressMode::eRepeat, //
                                      vk::SamplerAddressMode::eRepeat, //
                                      0.0f,                            //
                                      false,                           //
                                      16.0f,                           //
                                      false,                           //
                                      vk::CompareOp::eNever, 0.0f,     //
                                      std::numeric_limits<float>::max(),
                                      vk::BorderColor::eFloatOpaqueBlack);

    m_sampler = LOGICAL_DEVICE_INSTANCE.createSamplerUnique(samplerInfo);
}

void
Texture::allocDescriptorSet(const std::string& alloc_name,
                            const DescriptorManager& desc_manager)
{

    desc_manager.getAllocator(alloc_name).allocate(m_descriptor_set);

    vk::DescriptorImageInfo imageInfo(m_sampler.get(), m_image.view(),
                                      vk::ImageLayout::eShaderReadOnlyOptimal);
    vk::WriteDescriptorSet descriptorWrite(
        m_descriptor_set.get(), 0, 0, 1,
        vk::DescriptorType::eCombinedImageSampler, &imageInfo, nullptr,
        nullptr);

    LOGICAL_DEVICE_INSTANCE.updateDescriptorSets(1, &descriptorWrite, 0,
                                                 nullptr);
}

// const vk::DescriptorSet&
// Texture::getDescriptorSet() const
// {
//     return m_descriptor_set.get();
// }

void
Texture::bind(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const
{
    command_buffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                      pipelayout, 1u, 1,
                                      &(m_descriptor_set.get()), 0, nullptr);
}

bool
operator==(const Texture& left, const Texture& right)
{
    return (left.m_descriptor_set.get() == right.m_descriptor_set.get());
}
}; // namespace render
}; // namespace kusengine
