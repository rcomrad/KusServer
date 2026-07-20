#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/utils/vk_converter.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace window
{
class Surface;
class SurfaceCharacteristics;
} // namespace window

namespace pipeline
{

class SwapChain : public vk::SwapchainKHR
{
public:
    SwapChain(logic::Device& a_logic_device,
              window::Surface& a_serface,
              const window::SurfaceCharacteristics& a_characteristic);
    ~SwapChain();
    HOLY_TRINITY_ONLY_MOVE(SwapChain);

    VK_CONVERTER(vk::SwapchainKHR);

private:
    logic::Device& m_logic_device;

    static vk::SwapchainKHR create(
        logic::Device& a_logic_device,
        window::Surface& a_serface,
        const window::SurfaceCharacteristics& a_characteristic);
};

} // namespace pipeline

} // namespace gpu
