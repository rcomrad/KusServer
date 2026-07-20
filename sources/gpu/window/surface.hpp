#pragma once

#include <vulkan/vulkan.hpp>
//*************************
#include <GLFW/glfw3.h>
//*************************
#include "kernel/utility/macroses/holy_trinity.hpp"

#include "gpu/utils/vk_converter.hpp"

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

class Surface : public vk::SurfaceKHR
{
public:
    Surface(hard::Instance& a_instance,
            hard::Device& a_device,
            Window& a_window);
    ~Surface();
    HOLY_TRINITY_ONLY_MOVE(Surface);

    VK_CONVERTER(vk::SurfaceKHR);

private:
    hard::Instance& m_instance;

    static vk::SurfaceKHR create(hard::Instance& a_instance,
                                 hard::Device& a_device,
                                 Window& a_window);
};

} // namespace window

} // namespace gpu
