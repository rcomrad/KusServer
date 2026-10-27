#pragma once

#include <vulkan/vulkan.hpp>
//*************************
#include <GLFW/glfw3.h>
//*************************
#include "kernel/utility/macroses/holy_trinity.hpp"

#include "gpu/utils/vk_converter.hpp"
#include "gpu/utils/vulkan_move_monitor.hpp"

namespace gpu
{

namespace hard
{
class Device;
class Instance;
} // namespace hard

namespace window
{

class Window;

DECLARE_UNIQUE_WRAPPER_INSTANCE_HELPERS(SurfaceKHR);
class Surface : public SurfaceKHRBase
{
public:
    Surface(hard::Instance& a_instance,
            hard::Device& a_device,
            Window& a_window);

private:
    static vk::SurfaceKHR create(hard::Instance& a_instance,
                                 hard::Device& a_device,
                                 Window& a_window);
};

} // namespace window

} // namespace gpu
