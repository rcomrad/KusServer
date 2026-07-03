#pragma once

#include "kernel/framework/logger/basic/include_me.hpp"
#include <vulkan/vulkan.hpp>

namespace gpu::hard
{

class DebugCallback
{
public:
    void subscribe(vk::Instance a_instance);

    static std::string getMsgType(vk::DebugUtilsMessageTypeFlagBitsEXT a_type);

private:
    using UniqueDebugUtilsMessengerExt =
        vk::UniqueHandle<vk::DebugUtilsMessengerEXT,
                         vk::detail::DispatchLoaderDynamic>;
    UniqueDebugUtilsMessengerExt m_messenger;

    vk::detail::DispatchLoaderDynamic m_dispatch;

    static vk::DebugUtilsMessengerCreateInfoEXT generateCreateInfo() noexcept;
};

} // namespace gpu::hard
