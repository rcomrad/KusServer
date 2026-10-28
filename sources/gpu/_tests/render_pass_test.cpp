#include "vulkan_fixture.hpp"

#include <vulkan/vulkan.hpp>

#include "gpu/pipeline/render_pass.hpp"

namespace kustest
{

class RenderPassTest : public VulkanFixture
{
};

TEST_F(RenderPassTest, CreatesRenderPassForColorFormat)
{
    EXPECT_NO_THROW(
        gpu::pipeline::RenderPass render_pass(device(),
                                             vk::Format::eB8G8R8A8Srgb));
}

} // namespace kustest
