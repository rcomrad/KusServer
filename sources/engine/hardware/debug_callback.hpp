#pragma once

#include <vulkan/vulkan.hpp>

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::hard
{

class DebugCallback
{
public:
    void subscribe(vk::Instance a_instance);

    static const char* getMsgType(vk::DebugUtilsMessageTypeFlagBitsEXT a_type);

private:
    using UniqueDebugUtilsMessengerExt =
        vk::UniqueHandle<vk::DebugUtilsMessengerEXT,
                         vk::detail::DispatchLoaderDynamic>;
    UniqueDebugUtilsMessengerExt m_messenger;

    vk::detail::DispatchLoaderDynamic m_dispatch;

    static vk::DebugUtilsMessengerCreateInfoEXT generateCreateInfo() noexcept;
};

} // namespace engine::hard
