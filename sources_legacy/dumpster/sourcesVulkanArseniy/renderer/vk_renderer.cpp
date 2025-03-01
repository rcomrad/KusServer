#include "vk_renderer.hpp"

#include <vector>

#include "dds_structs.hpp"
#include "defines.h"
#include "game.hpp"
#include "shared_render_types.hpp"
#include "vk_init.hpp"
#include "vk_types.hpp"
#include "vk_util.hpp"

bool
vk_init(VkContext* vk_context, GLFWwindow* window)
{
    // Screen Rect
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        vk_context->screen_rect.extent.height = height;
        vk_context->screen_rect.extent.width  = width;
    }
    /////////////////////////// create instance
    VkApplicationInfo app_info = {};
    app_info.sType             = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName  = "Pong";
    app_info.pEngineName       = "engine";

    std::vector<const char*> enabled_extensions;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        enabled_extensions.push_back(glfwExtensions[i]);
    }
    enabled_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    // validation Layers
    const char* validation_layers[] = {"VK_LAYER_KHRONOS_validation"};

    VkInstanceCreateInfo instance_info = {};
    instance_info.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo     = &app_info;
    instance_info.enabledExtensionCount   = enabled_extensions.size();
    instance_info.ppEnabledExtensionNames = enabled_extensions.data();
    instance_info.enabledLayerCount       = ArraySize(validation_layers);
    instance_info.ppEnabledLayerNames     = validation_layers;

    VK_CHECK(vkCreateInstance(&instance_info, 0, &vk_context->instance));
    ///////////////////////////

    /////////////////////////// create debug messenger

    auto vkCreateDebugUtilsMessengerEXT =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            vk_context->instance, "vkCreateDebugUtilsMessengerEXT");

    if (vkCreateDebugUtilsMessengerEXT)
    {
        VkDebugUtilsMessengerCreateInfoEXT debug_info = {};
        debug_info.sType =
            VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debug_info.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
        debug_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

        debug_info.pfnUserCallback = vk_debug_callback;

        vkCreateDebugUtilsMessengerEXT(vk_context->instance, &debug_info, 0,
                                       &vk_context->debug_messenger);
    }
    else
    {
        return false;
    }
    ///////////////////////////
    // create Surface
    {
        VK_CHECK(glfwCreateWindowSurface(vk_context->instance, window, NULL,
                                         &vk_context->surface));
    }

    // choose GPU
    {
        vk_context->graphics_index = -1;

        uint32_t gpu_count = 0;

        VkPhysicalDevice gpus[10];

        VK_CHECK(
            vkEnumeratePhysicalDevices(vk_context->instance, &gpu_count, 0));
        VK_CHECK(
            vkEnumeratePhysicalDevices(vk_context->instance, &gpu_count, gpus));

        for (uint32_t i = 0; i < gpu_count; ++i)
        {
            VkPhysicalDevice gpu = gpus[i];

            uint32_t queue_family_count = 0;

            VkQueueFamilyProperties queue_props[10];

            vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count,
                                                     0);

            vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count,
                                                     queue_props);

            for (uint32_t j = 0; j < queue_family_count; ++j)
            {

                if (queue_props[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    VkBool32 surface_support = VK_FALSE;
                    VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(
                        gpu, j, vk_context->surface, &surface_support));

                    if (surface_support)
                    {
                        vk_context->graphics_index = j;
                        vk_context->gpu            = gpu;
                        break;
                    }
                }
            }
        }

        if (vk_context->graphics_index < 0)
        {
            return false;
        }
    }

    // Logical Device
    {
        float queue_priority = 1.f;

        VkDeviceQueueCreateInfo queue_info = {};
        queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_info.pQueuePriorities = &queue_priority;
        queue_info.queueFamilyIndex = vk_context->graphics_index;
        queue_info.queueCount       = 1;

        const char* swapchain_extensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        VkDeviceCreateInfo device_info   = {};
        device_info.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_info.pQueueCreateInfos    = &queue_info;
        device_info.queueCreateInfoCount = 1;
        device_info.enabledExtensionCount   = ArraySize(swapchain_extensions);
        device_info.ppEnabledExtensionNames = swapchain_extensions;

        VK_CHECK(vkCreateDevice(vk_context->gpu, &device_info, 0,
                                &vk_context->device));

        vkGetDeviceQueue(vk_context->device, vk_context->graphics_index, 0,
                         &vk_context->graphics_queue);
    }

    // Swap Chain
    {
        uint32_t format_count = 0;
        VkSurfaceFormatKHR surface_formats[10];
        VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(
            vk_context->gpu, vk_context->surface, &format_count, 0));
        VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(
            vk_context->gpu, vk_context->surface, &format_count,
            surface_formats));

        for (uint32_t i = 0; i < format_count; ++i)
        {
            VkSurfaceFormatKHR format = surface_formats[i];

            if (format.format == VK_FORMAT_R8G8B8A8_UNORM)
            {
                vk_context->surface_format = format;
                break;
            }
        }

        VkSurfaceCapabilitiesKHR surface_caps = {};
        VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
            vk_context->gpu, vk_context->surface, &surface_caps));

        uint32_t image_count = 0;
        image_count          = surface_caps.minImageCount + 1;

        image_count = image_count > surface_caps.maxImageCount ? image_count - 1
                                                               : image_count;

        VkSwapchainCreateInfoKHR swapchain_info = {};
        swapchain_info.sType      = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchain_info.compositeAlpha   = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchain_info.surface          = vk_context->surface;
        swapchain_info.imageFormat      = vk_context->surface_format.format;
        swapchain_info.preTransform     = surface_caps.currentTransform;
        swapchain_info.imageExtent      = surface_caps.currentExtent;
        swapchain_info.minImageCount    = image_count;
        swapchain_info.imageArrayLayers = 1;

        VkImageCreateInfo image_info = image_create_info();

        VK_CHECK(vkCreateImage(vk_context->device, &image_info, 0,
                               vk_context->swapchain_images));

        VK_CHECK(vkCreateSwapchainKHR(vk_context->device, &swapchain_info, 0,
                                      &vk_context->swapchain));

        VK_CHECK(
            vkGetSwapchainImagesKHR(vk_context->device, vk_context->swapchain,
                                    &vk_context->swapchain_image_count, 0));
        VK_CHECK(vkGetSwapchainImagesKHR(
            vk_context->device, vk_context->swapchain,
            &vk_context->swapchain_image_count, vk_context->swapchain_images));

        // Create the image views
        {
            VkImageViewCreateInfo view_info = {};

            view_info.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            view_info.format   = vk_context->surface_format.format;
            view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            view_info.subresourceRange.layerCount = 1;
            view_info.subresourceRange.levelCount = 1;

            for (uint32_t i = 0; i < vk_context->swapchain_image_count; ++i)
            {
                view_info.image = vk_context->swapchain_images[i];
                VK_CHECK(vkCreateImageView(vk_context->device, &view_info, 0,
                                           &vk_context->sc_image_views[i]));
            }
        }
    }

    // Render Path
    {
        VkAttachmentDescription attachment = {};
        attachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
        attachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        attachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
        attachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
        attachment.format                  = vk_context->surface_format.format;

        VkAttachmentReference color_attachmnet_ref = {};
        color_attachmnet_ref.attachment            = 0;
        color_attachmnet_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass_description = {};
        subpass_description.colorAttachmentCount = 1;
        subpass_description.pColorAttachments    = &color_attachmnet_ref;

        VkAttachmentDescription attachments[] = {attachment};

        VkRenderPassCreateInfo renderpass_info = {};
        renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderpass_info.attachmentCount = ArraySize(attachments);
        renderpass_info.pAttachments    = attachments;
        renderpass_info.subpassCount    = 1;
        renderpass_info.pSubpasses      = &subpass_description;
        VK_CHECK(vkCreateRenderPass(vk_context->device, &renderpass_info, 0,
                                    &vk_context->renderpass));
    }
    // Frame Buffer
    {
        VkFramebufferCreateInfo frame_buffer_info = {};
        frame_buffer_info.sType  = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frame_buffer_info.height = vk_context->screen_rect.extent.height;
        frame_buffer_info.width  = vk_context->screen_rect.extent.width;
        frame_buffer_info.renderPass      = vk_context->renderpass;
        frame_buffer_info.layers          = 1;
        frame_buffer_info.attachmentCount = 1;

        for (uint32_t i = 0; i < vk_context->swapchain_image_count; ++i)
        {
            frame_buffer_info.pAttachments = &vk_context->sc_image_views[i];
            VK_CHECK(vkCreateFramebuffer(vk_context->device, &frame_buffer_info,
                                         0, &vk_context->frame_buffer[i]));
        }
    }
    // Command Pool
    {
        VkCommandPoolCreateInfo command_pool_info = {};
        command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        command_pool_info.queueFamilyIndex = vk_context->graphics_index;
        command_pool_info.flags =
            VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        VK_CHECK(vkCreateCommandPool(vk_context->device, &command_pool_info, 0,
                                     &vk_context->command_pool));
    }

    // Command Buffer
    {
        VkCommandBufferAllocateInfo alloc_info =
            cmd_alloc_info(vk_context->command_pool);
        VK_CHECK(vkAllocateCommandBuffers(vk_context->device, &alloc_info,
                                          &vk_context->cmd));
    }

    // Sync Objects
    {
        VkSemaphoreCreateInfo semaphore_info = {};
        semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VK_CHECK(vkCreateSemaphore(vk_context->device, &semaphore_info, 0,
                                   &vk_context->acuire_semaphore));

        VK_CHECK(vkCreateSemaphore(vk_context->device, &semaphore_info, 0,
                                   &vk_context->submit_semaphore));

        VkFenceCreateInfo fenceInfo = fence_info(VK_FENCE_CREATE_SIGNALED_BIT);
        VK_CHECK(vkCreateFence(vk_context->device, &fenceInfo, 0,
                               &vk_context->imgAvailableFence));
    }
    // Create Descriptor Set Layouts
    {

        VkDescriptorSetLayoutBinding layout_bindings[] = {
            layout_binding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                           VK_SHADER_STAGE_VERTEX_BIT, 1, 0),
            layout_binding(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                           VK_SHADER_STAGE_VERTEX_BIT, 1, 1),
            layout_binding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                           VK_SHADER_STAGE_FRAGMENT_BIT, 1, 2)};

        VkDescriptorSetLayoutCreateInfo layoutInfo = {};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = ArraySize(layout_bindings);
        layoutInfo.pBindings    = layout_bindings;

        VK_CHECK(vkCreateDescriptorSetLayout(vk_context->device, &layoutInfo, 0,
                                             &vk_context->set_layout));
    }

    // Create Pipeline Layout
    {
        VkPipelineLayoutCreateInfo layoutInfo = {};
        layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        layoutInfo.setLayoutCount = 1;
        layoutInfo.pSetLayouts    = &vk_context->set_layout;
        VK_CHECK(vkCreatePipelineLayout(vk_context->device, &layoutInfo, 0,
                                        &vk_context->pipeline_layout));
    }

    // Pipeline
    {
        VkShaderModule vertex_shader, fragment_shader;
        // Vertex Shader
        {
            uint32_t size = 0;
            uint32_t* vertexCode =
                (uint32_t*)read_file("C:/Users/arsbo/source/repos/vulkan "
                                     "triangle/assets/shaders/shader.vert.spv",
                                     size);

            VkShaderModuleCreateInfo shader_module_info = {};
            shader_module_info.sType =
                VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            shader_module_info.pCode    = vertexCode;
            shader_module_info.codeSize = size;
            VK_CHECK(vkCreateShaderModule(
                vk_context->device, &shader_module_info, 0, &vertex_shader));
        }
        // Fragment Shader
        {
            uint32_t size = 0;
            uint32_t* fragmentCode =
                (uint32_t*)read_file("C:/Users/arsbo/source/repos/vulkan "
                                     "triangle/assets/shaders/shader.frag.spv",
                                     size);

            VkShaderModuleCreateInfo shader_module_info = {};
            shader_module_info.sType =
                VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            shader_module_info.pCode    = fragmentCode;
            shader_module_info.codeSize = size;
            VK_CHECK(vkCreateShaderModule(
                vk_context->device, &shader_module_info, 0, &fragment_shader));
        }

        VkPipelineMultisampleStateCreateInfo multisample_state = {};
        multisample_state.sType =
            VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
        input_assembly.sType =
            VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        VkPipelineShaderStageCreateInfo vert_stage = {};
        vert_stage.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vert_stage.stage  = VK_SHADER_STAGE_VERTEX_BIT;
        vert_stage.pName  = "main";
        vert_stage.module = vertex_shader;

        VkPipelineShaderStageCreateInfo frag_stage = {};
        frag_stage.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        frag_stage.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
        frag_stage.pName  = "main";
        frag_stage.module = fragment_shader;

        VkPipelineShaderStageCreateInfo shader_stages[] = {vert_stage,
                                                           frag_stage};

        VkPipelineVertexInputStateCreateInfo vertex_input_state = {};
        vertex_input_state.sType =
            VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        VkPipelineColorBlendAttachmentState color_blend_attachment = {};
        color_blend_attachment.colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        color_blend_attachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo color_blend_state = {};
        color_blend_state.sType =
            VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        color_blend_state.pAttachments    = &color_blend_attachment;
        color_blend_state.attachmentCount = 1;

        VkPipelineRasterizationStateCreateInfo rasterization_state = {};
        rasterization_state.sType =
            VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterization_state.cullMode    = VK_CULL_MODE_BACK_BIT;
        rasterization_state.frontFace   = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
        rasterization_state.lineWidth   = 1.0f;

        VkRect2D scissor    = {};
        VkViewport viewport = {};

        VkPipelineViewportStateCreateInfo viewport_state = {};
        viewport_state.sType =
            VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state.pViewports    = &viewport;
        viewport_state.viewportCount = 1;
        viewport_state.pScissors     = &scissor;
        viewport_state.scissorCount  = 1;

        VkDynamicState dynamic_states[]{VK_DYNAMIC_STATE_VIEWPORT,
                                        VK_DYNAMIC_STATE_SCISSOR};

        VkPipelineDynamicStateCreateInfo dynamic_state = {};
        dynamic_state.sType =
            VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic_state.pDynamicStates    = dynamic_states;
        dynamic_state.dynamicStateCount = ArraySize(dynamic_states);

        VkGraphicsPipelineCreateInfo pipeline_info = {};
        pipeline_info.sType  = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.layout = vk_context->pipeline_layout;
        pipeline_info.renderPass          = vk_context->renderpass;
        pipeline_info.pColorBlendState    = &color_blend_state;
        pipeline_info.pVertexInputState   = &vertex_input_state;
        pipeline_info.pStages             = shader_stages;
        pipeline_info.stageCount          = ArraySize(shader_stages);
        pipeline_info.pRasterizationState = &rasterization_state;
        pipeline_info.pViewportState      = &viewport_state;
        pipeline_info.pDynamicState       = &dynamic_state;
        pipeline_info.pInputAssemblyState = &input_assembly;
        pipeline_info.pMultisampleState   = &multisample_state;

        VK_CHECK(vkCreateGraphicsPipelines(vk_context->device, 0, 1,
                                           &pipeline_info, 0,
                                           &vk_context->pipeline));

        (vkDestroyShaderModule(vk_context->device, vertex_shader, 0));
        (vkDestroyShaderModule(vk_context->device, fragment_shader, 0));
    }

    // Staging Buffer
    {
        vk_context->staging_buffer =
            vk_allocate_buffer(vk_context->device, vk_context->gpu, MB(7),
                               VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                               VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
    }

    // Create Image
    {
        uint32_t file_size = 0;
        auto data = (DDSFile*)(read_file("C:/Users/arsbo/source/repos/vulkan "
                                         "triangle/assets/textures/human.dds",
                                         file_size));

        uint32_t texture_size = data->header.Width * data->header.Height * 4;

        memcpy(vk_context->staging_buffer.data, &data->data_begin,
               texture_size);

        vk_context->image = vk_allocate_image(
            vk_context->device, vk_context->gpu, data->header.Width,
            data->header.Height, VK_FORMAT_R8G8B8_UNORM);

        VkCommandBuffer cmd = {};
        VkCommandBufferAllocateInfo cmd_alloc =
            cmd_alloc_info(vk_context->command_pool);
        VK_CHECK(
            vkAllocateCommandBuffers(vk_context->device, &cmd_alloc, &cmd));

        VkCommandBufferBeginInfo begin_info = cmd_begin_info();
        VK_CHECK(vkBeginCommandBuffer(cmd, &begin_info));

        VkImageSubresourceRange range = {};
        range.aspectMask              = VK_IMAGE_ASPECT_COLOR_BIT;
        range.layerCount              = 1;
        range.levelCount              = 1;

        // Transition Layout to Transfer optimal
        VkImageMemoryBarrier imgMemBarrier = {};
        imgMemBarrier.sType            = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imgMemBarrier.image            = vk_context->image.image;
        imgMemBarrier.oldLayout        = VK_IMAGE_LAYOUT_UNDEFINED;
        imgMemBarrier.newLayout        = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        imgMemBarrier.srcAccessMask    = VK_ACCESS_TRANSFER_READ_BIT;
        imgMemBarrier.dstAccessMask    = VK_ACCESS_TRANSFER_WRITE_BIT;
        imgMemBarrier.subresourceRange = range;

        vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT,
                             VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, 0, 0, 0, 1,
                             &imgMemBarrier);

        VkBufferImageCopy copy_region = {};
        copy_region.imageExtent = {data->header.Width, data->header.Height, 1};
        copy_region.imageSubresource.layerCount = 1;
        copy_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vkCmdCopyBufferToImage(
            cmd, vk_context->staging_buffer.buffer, vk_context->image.image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy_region);

        imgMemBarrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        imgMemBarrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imgMemBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        imgMemBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT,
                             VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, 0, 0,
                             0, 1, &imgMemBarrier);

        VK_CHECK(vkEndCommandBuffer(cmd));

        VkFence uploadFence;
        VkFenceCreateInfo fenceInfo = fence_info();
        VK_CHECK(
            vkCreateFence(vk_context->device, &fenceInfo, 0, &uploadFence));

        VkSubmitInfo submitInfo = submit_info(&cmd);
        VK_CHECK(vkQueueSubmit(vk_context->graphics_queue, 1, &submitInfo,
                               uploadFence));

        VK_CHECK(vkWaitForFences(vk_context->device, 1, &uploadFence, true,
                                 UINT64_MAX));
    }

    // Create Image View
    {
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType  = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image  = vk_context->image.image;
        viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.layerCount = 1;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.viewType                    = VK_IMAGE_VIEW_TYPE_2D;

        VK_CHECK(vkCreateImageView(vk_context->device, &viewInfo, 0,
                                   &vk_context->image.view));
    }

    // Create Sampler
    {
        VkSamplerCreateInfo samplerInfo = {};
        samplerInfo.sType               = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.minFilter           = VK_FILTER_NEAREST;
        samplerInfo.magFilter           = VK_FILTER_NEAREST;

        VK_CHECK(vkCreateSampler(vk_context->device, &samplerInfo, 0,
                                 &vk_context->sampler));
    }

    // Create Transform Sorage Buffer
    {
        vk_context->transform_storage_buffer =
            vk_allocate_buffer(vk_context->device, vk_context->gpu,
                               sizeof(Transform) * MAX_ENTITIES,
                               VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                               VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
    }

    // Create Global Uniform Buffer Object
    {
        vk_context->globalUBO = vk_allocate_buffer(
            vk_context->device, vk_context->gpu, sizeof(GlobalData),
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

        GlobalData globalData = {(int)vk_context->screen_rect.extent.width,
                                 (int)vk_context->screen_rect.extent.height};

        memcpy(vk_context->globalUBO.data, &globalData, sizeof(globalData));
    }

    // Create Index Buffer
    {
        vk_context->indexBuffer = vk_allocate_buffer(
            vk_context->device, vk_context->gpu, sizeof(uint32_t) * 6,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        // std::cout << "cont\n" << vk_context->indexBuffer.data << '\n';

        // Copy Indices to the buffer
        {
            uint32_t indices[] = {0, 1, 2, 2, 3, 0};

            memcpy(vk_context->indexBuffer.data, &indices,
                   sizeof(uint32_t) * 6);
        }
    }

    // Create Descriptor Pool
    {
        VkDescriptorPoolSize poolSizes[] = {
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1},
            {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1}
        };

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.maxSets       = 1;
        poolInfo.poolSizeCount = ArraySize(poolSizes);
        poolInfo.pPoolSizes    = poolSizes;
        VK_CHECK(vkCreateDescriptorPool(vk_context->device, &poolInfo, 0,
                                        &vk_context->desc_pool));
    }

    // Create Descriptor Set
    {
        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType       = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.pSetLayouts = &vk_context->set_layout;
        allocInfo.descriptorSetCount = 1;
        allocInfo.descriptorPool     = vk_context->desc_pool;
        VK_CHECK(vkAllocateDescriptorSets(vk_context->device, &allocInfo,
                                          &vk_context->desc_set));
    }
    // Update Descriptor Set
    {
        DescriptorInfo descInfos[] = {
            DescriptorInfo(vk_context->globalUBO.buffer),
            DescriptorInfo(vk_context->transform_storage_buffer.buffer),
            DescriptorInfo(vk_context->sampler, vk_context->image.view)};

        VkWriteDescriptorSet writes[] = {
            write_set(vk_context->desc_set, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                      &descInfos[0], 0, 1),
            write_set(vk_context->desc_set, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                      &descInfos[1], 1, 1),
            write_set(vk_context->desc_set,
                      VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, &descInfos[2],
                      2, 1)};

        vkUpdateDescriptorSets(vk_context->device, ArraySize(writes), writes, 0,
                               0);
    }

    return true;
}

bool
vk_render(VkContext* vkcontext, GameState* gameState)
{
    uint32_t imgIdx;

    // We wait on the GPU to be done with the work
    VK_CHECK(vkWaitForFences(vkcontext->device, 1,
                             &vkcontext->imgAvailableFence, VK_TRUE,
                             UINT64_MAX));
    VK_CHECK(
        vkResetFences(vkcontext->device, 1, &vkcontext->imgAvailableFence));

    // Copy transforms to the buffer
    {
        memcpy(vkcontext->transform_storage_buffer.data, &gameState->entities,
               sizeof(Transform) * gameState->entityCount);
    }

    // This waits on the timeout until the image is ready, if timeout reached ->
    // VK_TIMEOUT
    VK_CHECK(vkAcquireNextImageKHR(vkcontext->device, vkcontext->swapchain,
                                   UINT64_MAX, vkcontext->acuire_semaphore, 0,
                                   &imgIdx));

    VkCommandBuffer cmd = vkcontext->cmd;
    vkResetCommandBuffer(cmd, 0);

    VkCommandBufferBeginInfo beginInfo = cmd_begin_info();
    VK_CHECK(vkBeginCommandBuffer(cmd, &beginInfo));

    // Clear Color to Yellow
    VkClearValue clearValue = {};
    clearValue.color        = {1, 1, 0, 1};

    VkRenderPassBeginInfo rpBeginInfo = {};
    rpBeginInfo.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpBeginInfo.renderArea.extent = vkcontext->screen_rect.extent;
    rpBeginInfo.clearValueCount   = 1;
    rpBeginInfo.pClearValues      = &clearValue;
    rpBeginInfo.renderPass        = vkcontext->renderpass;
    rpBeginInfo.framebuffer       = vkcontext->frame_buffer[imgIdx];
    vkCmdBeginRenderPass(cmd, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Rendering Commands
    {
        VkViewport viewport = {};
        viewport.maxDepth   = 1.0f;
        viewport.width      = vkcontext->screen_rect.extent.width;
        viewport.height     = vkcontext->screen_rect.extent.height;

        VkRect2D scissor = {};
        scissor.extent   = vkcontext->screen_rect.extent;

        vkCmdSetViewport(cmd, 0, 1, &viewport);
        vkCmdSetScissor(cmd, 0, 1, &scissor);

        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                vkcontext->pipeline_layout, 0, 1,
                                &vkcontext->desc_set, 0, 0);

        vkCmdBindIndexBuffer(cmd, vkcontext->indexBuffer.buffer, 0,
                             VK_INDEX_TYPE_UINT32);
        vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          vkcontext->pipeline);
        vkCmdDrawIndexed(cmd, 6, gameState->entityCount, 0, 0, 0);
    }

    vkCmdEndRenderPass(cmd);

    VK_CHECK(vkEndCommandBuffer(cmd));

    VkPipelineStageFlags waitStage =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    // This call will signal the Fence when the GPU Work is done
    VkSubmitInfo submitInfo         = submit_info(&cmd);
    submitInfo.pWaitDstStageMask    = &waitStage;
    submitInfo.pSignalSemaphores    = &vkcontext->submit_semaphore;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pWaitSemaphores      = &vkcontext->acuire_semaphore;
    submitInfo.waitSemaphoreCount   = 1;
    VK_CHECK(vkQueueSubmit(vkcontext->graphics_queue, 1, &submitInfo,
                           vkcontext->imgAvailableFence));

    VkPresentInfoKHR presentInfo   = {};
    presentInfo.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pSwapchains        = &vkcontext->swapchain;
    presentInfo.swapchainCount     = 1;
    presentInfo.pImageIndices      = &imgIdx;
    presentInfo.pWaitSemaphores    = &vkcontext->submit_semaphore;
    presentInfo.waitSemaphoreCount = 1;
    VK_CHECK(vkQueuePresentKHR(vkcontext->graphics_queue, &presentInfo));

    return true;
}
