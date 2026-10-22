#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include "kernel/utility/type/declaration/move_monitor.hpp"
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

DECLARE_UNIQUE_WRAPPER_HELPERS(SwapchainKHR);
class SwapChain : public SwapchainKHRBase
{
public:
    SwapChain(logic::Device& a_logic_device,
              window::Surface& a_serface,
              const window::SurfaceCharacteristics& a_characteristic);

private:
    static vk::SwapchainKHR create(
        logic::Device& a_logic_device,
        window::Surface& a_serface,
        const window::SurfaceCharacteristics& a_characteristic);
};

} // namespace pipeline

} // namespace gpu
