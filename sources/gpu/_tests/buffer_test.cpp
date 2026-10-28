#include "vulkan_fixture.hpp"

#include <array>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "kernel/framework/logger/basic/exception.hpp"

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/buffers/mapped_buffer.hpp"
#include "gpu/buffers/staging_buffer.hpp"

namespace kustest
{

class BufferTest : public VulkanFixture
{
protected:
    vk::UniqueBuffer createTransferSource(vk::DeviceSize a_size)
    {
        vk::BufferCreateInfo info;
        info.setSize(a_size).setUsage(vk::BufferUsageFlagBits::eTransferSrc);
        return device().createBufferUnique(info);
    }

    vk::UniqueImage createTransferImage(uint32_t a_width, uint32_t a_height)
    {
        vk::ImageCreateInfo info;
        info.setImageType(vk::ImageType::e2D)
            .setFormat(vk::Format::eR8G8B8A8Unorm)
            .setExtent(vk::Extent3D(a_width, a_height, 1))
            .setMipLevels(1)
            .setArrayLayers(1)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setTiling(vk::ImageTiling::eOptimal)
            .setUsage(vk::ImageUsageFlagBits::eTransferDst |
                      vk::ImageUsageFlagBits::eSampled)
            .setSharingMode(vk::SharingMode::eExclusive)
            .setInitialLayout(vk::ImageLayout::eUndefined);
        return device().createImageUnique(info);
    }
};

TEST_F(BufferTest, BaseBufferBindsBufferWithinCapacity)
{
    auto buffer       = createTransferSource(1024);
    auto requirements = device().getBufferMemoryRequirements(*buffer);

    gpu::buffer::BaseBuffer memory(
        device(), requirements.size, requirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eDeviceLocal);

    EXPECT_NO_THROW(memory.bind(*buffer));

    buffer.reset();
}

TEST_F(BufferTest, BaseBufferThrowsWhenCapacityIsExhausted)
{
    auto first        = createTransferSource(256);
    auto requirements = device().getBufferMemoryRequirements(*first);

    gpu::buffer::BaseBuffer memory(
        device(), requirements.size, requirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eDeviceLocal);
    memory.bind(*first);

    auto second = createTransferSource(256);
    EXPECT_THROW(memory.bind(*second), core::LoggerException);
}

TEST_F(BufferTest, MappedBufferAcceptsDataWithinCapacity)
{
    auto buffer       = createTransferSource(256);
    auto requirements = device().getBufferMemoryRequirements(*buffer);

    gpu::buffer::MappedBuffer memory(
        device(), requirements.size, requirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent);
    memory.bind(*buffer);

    const std::array<char, 16> data{};
    EXPECT_NO_THROW(memory.push(data.data(), data.size()));
    EXPECT_NO_THROW(memory.clear());
    EXPECT_NO_THROW(memory.push(data.data(), data.size()));

    buffer.reset();
}

TEST_F(BufferTest, MappedBufferRejectsDataThatDoesNotFit)
{
    auto buffer       = createTransferSource(256);
    auto requirements = device().getBufferMemoryRequirements(*buffer);

    gpu::buffer::MappedBuffer memory(
        device(), requirements.size, requirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent);
    memory.bind(*buffer);

    std::vector<char> data(requirements.size, 0x5A);
    EXPECT_THROW(memory.push(data.data(), data.size()),
                 core::LoggerException);
}

TEST_F(BufferTest, StagingBufferUploadsPixelsIntoImage)
{
    auto image        = createTransferImage(2, 2);
    auto image_req    = device().getImageMemoryRequirements(*image);

    gpu::buffer::BaseBuffer image_memory(
        device(), image_req.size, image_req.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eDeviceLocal);
    image_memory.bind(*image);

    std::array<char, 2 * 2 * 4> pixels{};
    pixels.fill(static_cast<char>(0x7F));

    gpu::buffer::StagingBuffer staging(device(), 64);

    EXPECT_NO_THROW(staging.transfer_image(
        queue(), commandPool(), *image, pixels.data(), {2, 2}));

    image.reset();
}

} // namespace kustest
