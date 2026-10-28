#include "vulkan_fixture.hpp"

#include <vulkan/vulkan.hpp>

#include "kernel/framework/logger/basic/exception.hpp"

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/command/base_command.hpp"
#include "gpu/command/one_time_command.hpp"

namespace kustest
{

class CommandTest : public VulkanFixture
{
};

TEST(CommandRangeTest, Base2DRangeTargetsOneColorLayerAndLevel)
{
    auto range = gpu::command::BaseCommand::base2DRange();

    EXPECT_EQ(range.aspectMask,
              vk::ImageAspectFlags(vk::ImageAspectFlagBits::eColor));
    EXPECT_EQ(range.baseMipLevel, 0u);
    EXPECT_EQ(range.levelCount, 1u);
    EXPECT_EQ(range.baseArrayLayer, 0u);
    EXPECT_EQ(range.layerCount, 1u);
}

TEST_F(CommandTest, AllocatesCommandBufferAndRecordsEmptyCommand)
{
    auto command = commandPool().alocateBuffer();

    EXPECT_NO_THROW(
        command.begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit));
    EXPECT_NO_THROW(command.end());
}

TEST_F(CommandTest, BeginTwiceThrows)
{
    auto command = commandPool().alocateBuffer();
    command.begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

    EXPECT_THROW(command.begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit),
                 core::LoggerException);

    // The first begin succeeded, so the command buffer can still be ended.
    EXPECT_NO_THROW(command.end());
}

TEST_F(CommandTest, EndWithoutBeginThrows)
{
    auto command = commandPool().alocateBuffer();

    EXPECT_THROW(command.end(), core::LoggerException);
}

TEST_F(CommandTest, AllocatesDrawCommandBuffersWithIndexes)
{
    auto commands = commandPool().alocateDrawBuffers(3);

    ASSERT_EQ(commands.size(), 3u);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(commands[i].index, i);
        EXPECT_NO_THROW(commands[i].begin());
        EXPECT_NO_THROW(commands[i].end());
    }
}

TEST_F(CommandTest, SubmitsOneTimeCommandSynchronously)
{
    // OneTimeCommand begins recording in its constructor.
    auto command = commandPool().alocateOneTimeCommand();
    command.end();

    EXPECT_NO_THROW(queue().synchronousSubmit(command));
}

TEST_F(CommandTest, RecordsImageLayoutBarriers)
{
    vk::ImageCreateInfo image_info;
    image_info.setImageType(vk::ImageType::e2D)
        .setFormat(vk::Format::eR8G8B8A8Unorm)
        .setExtent(vk::Extent3D(2, 2, 1))
        .setMipLevels(1)
        .setArrayLayers(1)
        .setSamples(vk::SampleCountFlagBits::e1)
        .setTiling(vk::ImageTiling::eOptimal)
        .setUsage(vk::ImageUsageFlagBits::eTransferDst |
                  vk::ImageUsageFlagBits::eSampled)
        .setSharingMode(vk::SharingMode::eExclusive)
        .setInitialLayout(vk::ImageLayout::eUndefined);

    auto image = device().createImageUnique(image_info);

    auto requirements = device().getImageMemoryRequirements(*image);
    gpu::buffer::BaseBuffer memory(
        device(), requirements.size, requirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eDeviceLocal);
    memory.bind(*image);

    auto command = commandPool().alocateBuffer();
    command.begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    command.pushBarrierFirstWrite(*image);
    command.pushBarrierReadPostWrite(*image);
    EXPECT_NO_THROW(command.end());

    image.reset();
}

} // namespace kustest
