#include "vulkan_fixture.hpp"

#include <array>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/buffers/staging_buffer.hpp"
#include "gpu/command/base_command.hpp"
#include "gpu/sprite/pixel_array.hpp"
#include "gpu/sprite/raw_texture.hpp"
#include "gpu/sprite/sprite.hpp"
#include "gpu/sprite/sprite_push_data.hpp"
#include "gpu/sprite/texture_info.hpp"

namespace kustest
{

namespace
{

gpu::sprite::PixelArray
makePixels(uint32_t a_width, uint32_t a_height)
{
    gpu::sprite::PixelArray result;
    result.allocated_buffer.assign(
        static_cast<size_t>(a_width) * a_height * 4, '\x7F');
    result.data_ptr = result.allocated_buffer.data();
    result.size     = gpu::type::CoordinateSize(a_width, a_height);
    return result;
}

} // namespace

class SpriteTest : public VulkanFixture
{
protected:
    vk::UniqueDescriptorSetLayout createDescriptorSetLayout()
    {
        std::vector<vk::DescriptorSetLayoutBinding> bindings;
        bindings.emplace_back()
            .setBinding(0)
            .setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
            .setDescriptorCount(1)
            .setStageFlags(vk::ShaderStageFlagBits::eFragment);

        vk::DescriptorSetLayoutCreateInfo info;
        info.setBindings(bindings);
        return device().createDescriptorSetLayoutUnique(info);
    }

    vk::UniqueDescriptorPool createDescriptorPool()
    {
        std::vector<vk::DescriptorPoolSize> sizes;
        sizes.emplace_back()
            .setType(vk::DescriptorType::eCombinedImageSampler)
            .setDescriptorCount(1);

        vk::DescriptorPoolCreateInfo info;
        info.setMaxSets(1)
            .setPoolSizeCount(static_cast<uint32_t>(sizes.size()))
            .setPPoolSizes(sizes.data());
        return device().createDescriptorPoolUnique(info);
    }

    vk::UniquePipelineLayout createPipelineLayout(
        vk::DescriptorSetLayout a_descriptor_set_layout)
    {
        std::vector<vk::DescriptorSetLayout> layouts{a_descriptor_set_layout};

        vk::PipelineLayoutCreateInfo info;
        info.setSetLayouts(layouts);
        return device().createPipelineLayoutUnique(info);
    }
};

TEST_F(SpriteTest, RawTextureCreatesImageAndReportsSize)
{
    gpu::sprite::RawTexture texture(device(), makePixels(2, 2));

    EXPECT_EQ(texture.getSize(), gpu::type::CoordinateSize(2, 2));

    auto requirements = texture.getMemReq(device());
    EXPECT_GT(requirements.size, 0u);

    auto image = texture.obtainImage();
    EXPECT_TRUE(static_cast<bool>(*image));
}

TEST_F(SpriteTest, SpriteBuildsViewAndPushData)
{
    gpu::sprite::RawTexture texture(device(), makePixels(2, 2));

    auto image_requirements = texture.getMemReq(device());
    gpu::buffer::BaseBuffer image_memory(
        device(), image_requirements.size, image_requirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eDeviceLocal);
    gpu::buffer::StagingBuffer staging(device(), 64);
    EXPECT_NO_THROW(texture.writeToBuffer(queue(), commandPool(), image_memory,
                                          staging));

    auto descriptor_layout = createDescriptorSetLayout();
    auto descriptor_pool   = createDescriptorPool();

    gpu::sprite::TextureInfo info;
    info.dimensions = gpu::type::Dimensions(1, 1);

    gpu::sprite::Sprite sprite(device(), *descriptor_layout, *descriptor_pool,
                               texture, info);

    auto view = sprite.generateSpriteView(4);
    EXPECT_EQ(view.sprite_id, 4);
    EXPECT_EQ(view.size, gpu::type::CoordinateSize(2, 2));
    EXPECT_EQ(view.hitbox_offset, gpu::type::Coordinates(0, 0));

    auto pipeline_layout = createPipelineLayout(*descriptor_layout);
    auto command         = commandPool().alocateBuffer();
    command.begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

    gpu::sprite::SpritePushData push{};
    push.coord_offset = {0.0f, 0.0f};
    sprite.draw(*pipeline_layout, command, push, 0);

    EXPECT_NO_THROW(command.end());

    EXPECT_FLOAT_EQ(push.coord_scaler.x, 1.0f);
    EXPECT_FLOAT_EQ(push.coord_scaler.y, 1.0f);
    EXPECT_FLOAT_EQ(push.coord_offset.x, 0.0f);
    EXPECT_FLOAT_EQ(push.coord_offset.y, 0.0f);
    EXPECT_FLOAT_EQ(push.uv_scaler.x, 1.0f);
    EXPECT_FLOAT_EQ(push.uv_scaler.y, 1.0f);
    EXPECT_FLOAT_EQ(push.uv_offset.x, 0.0f);
    EXPECT_FLOAT_EQ(push.uv_offset.y, 0.0f);
}

} // namespace kustest
