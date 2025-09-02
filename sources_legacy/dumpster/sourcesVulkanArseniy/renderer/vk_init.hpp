#ifndef VK_INIT_HPP
#define VK_INIT_HPP

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include "vk_types.hpp"

class VkContext;

VkCommandBufferBeginInfo
cmd_begin_info();

VkImageCreateInfo
image_create_info();

bool
vk_init(VkContext* vk_context, GLFWwindow* window);

bool
vk_render(VkContext* vk_context);

char*
read_file(const std::string& filename, uint32_t& size);

VkCommandBufferAllocateInfo
cmd_alloc_info(VkCommandPool pool);

VkSubmitInfo
submit_info(VkCommandBuffer* cmd, uint32_t cmdCount = 1);

VkFenceCreateInfo
fence_info(VkFenceCreateFlags flags = 0);

VkDescriptorSetLayoutBinding
layout_binding(VkDescriptorType type, VkShaderStageFlags shaderStages,
               uint32_t count, uint32_t bindingNumber);

VkWriteDescriptorSet
write_set(VkDescriptorSet set, VkDescriptorType type, DescriptorInfo* descInfo,
          uint32_t bindingNumber, uint32_t count);

#endif // VK_INIT_HPP