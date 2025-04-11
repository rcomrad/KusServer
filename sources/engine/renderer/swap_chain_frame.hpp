#ifndef SWAP_CHAIN_FRAME
#define SWAP_CHAIN_FRAME

#include <vulkan/vulkan.hpp>

namespace kusengine
{
class SwapChainFrame
{
public:
    void createFrame(const vk::Device& logical_device,
                     const vk::Image& image,
                     const vk::Format& format);

private:
    vk::UniqueImage m_image;
    vk::UniqueImageView m_view;
};
}; // namespace kusengine
#endif // SWAP_CHAIN_FRAME
