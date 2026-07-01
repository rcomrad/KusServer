
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include "debug_callback.hpp"

#include <vulkan/vulkan.hpp>

// ******

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace
{

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT a_severity,
              VkDebugUtilsMessageTypeFlagsEXT a_type,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
              void* pUserData)
{
    auto type = gpu::hard::DebugCallback::getMsgType(
        static_cast<vk::DebugUtilsMessageTypeFlagBitsEXT>(a_type));

    std::string log_msg =
        std::format("Vulkan {} log: {}", type, pCallbackData->pMessage);

    // To print object address
    // for (decltype(pCallbackData->objectCount) i = 0;
    //      i < pCallbackData->objectCount; i++)
    // {
    //     log_msg +=
    //         std::format("\n\t{}", pCallbackData->pObjects[i].objectHandle);
    // }

    switch (static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(a_severity))
    {
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
            LOG_SPAM("%s", log_msg);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
            LOG_SPAM("%s", log_msg);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
            LOG_WARNING("%s", log_msg);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
            LOG_ERROR("%s", log_msg);
            break;
        default:
            THROW("Invalid severity code %d", static_cast<int>(a_severity));
    }

    return VK_FALSE; // The calling function should not be aborted
}

}; // namespace

namespace gpu::hard
{

/*****************************************************************************/
// auto void_ptr = a_instance.getProcAddr("vkCreateDebugUtilsMessengerEXT");
// if (void_ptr == nullptr)
// {
//     THROW("No debug messenger");
// }
// auto func_ptr =
//     reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(void_ptr);

// auto info = generateCreateInfo();
// VkResult res = func_ptr(
//     &(*a_instance),
//     reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&info),
//     NULL, m_messenger);
// if (!res)
// {
//     THROW("debug utils messenger");
// }
/*****************************************************************************/
// m_messenger = a_instance.createDebugUtilsMessengerEXTUnique(
//     generateCreateInfo(), nullptr,
//     ::vk::detail::getDispatchLoaderStatic());
//     vk::detail::DispatchLoaderDynamic(&vkGetInstanceProcAddr);
/*****************************************************************************/

void
DebugCallback::subscribe(vk::Instance a_instance)
{
    SCOPED_TRACE_FUNC("Subscribe to debug message callback");

    static vk::detail::DynamicLoader dl;
    auto vkGetInstanceProcAddr =
        dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(a_instance);
    m_messenger =
        a_instance.createDebugUtilsMessengerEXTUnique(generateCreateInfo());
}

vk::DebugUtilsMessengerCreateInfoEXT
DebugCallback::generateCreateInfo() noexcept
{
    vk::DebugUtilsMessengerCreateInfoEXT info;

    info.setMessageSeverity(vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
                            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError)
        .setMessageType(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance)
        .setPfnUserCallback(&debugCallback);

    return info;
}

std::string
DebugCallback::getMsgType(vk::DebugUtilsMessageTypeFlagBitsEXT a_type)
{
    using std::string_literals::operator""s;
    switch (a_type)
    {
        case vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral:
            return "general";
        case vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation:
            return "validation";
        case vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance:
            return "performance";
        case vk::DebugUtilsMessageTypeFlagBitsEXT::eDeviceAddressBinding:
            return "device address binding";
        default:
            return "invalid ("s +
                   vk::toHexString(static_cast<uint32_t>(a_type)) + ")"s;
    }
}

} // namespace gpu::hard
