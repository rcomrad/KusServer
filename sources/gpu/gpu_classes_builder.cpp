#include "gpu_classes_builder.hpp"

#include "font/font_loader.hpp"
#include "font/font_storage.hpp"
#include "font/font_storage_builder.hpp"
#include "hardware/manager.hpp"
#include "logic/manager.hpp"
#include "pipeline/manager.hpp"
#include "sprite/image_loader.hpp"
#include "sprite/sprite_storage.hpp"
#include "sprite/storage_builder.hpp"
#include "window/manager.hpp"

#include "presenter.hpp"
#include "resource_storage.hpp"
#include "vulkan_manager.hpp"

gpu::buildGpuClasses()
{
    //*************************************
    // Vulkan manafers
    //*************************************

    hard::Manager hard_manager;

    auto& instance    = hard_manager.getInstance();
    auto& hard_device = hard_manager.getDevice();
    window::Manager window_manager(instance, hard_device);

    const auto& characteristics = window_manager.getCharacteristics();
    logic::Manager logic_manager(hard_device, characteristics.family_index);

    auto& logic_device = logic_manager.getDevice();
    auto& surface      = window_manager.getSurface();
    pipeline::Manager pipeline_manager(logic_device, surface, characteristics);

    //*************************************
    // Storages
    //*************************************

    sprite::SpriteStorageBuilder sprite_builder(logic_device);
    font::FontStorageBuilder font_builder(sprite_builder);

    sprite::loadAllImages(sprite_builder);
    font::loadAllFonts(font_builder);

    auto& queue           = m_logic_manager.getQueue();
    auto& cmd_pool        = m_logic_manager.getCommandPool();
    auto& desc_set_layout = m_pipeline_manager.getDescSetLayout();

    auto sprite_storage = builder.collapse(queue, cmd_pool, desc_set_layout);
    auto font_storage   = font_builder.collapse(sprite_storage);

    //*************************************
    // Construct global manager
    //*************************************

    VulkanManager manager(std::move(hard_manager), std::move(window_manager),
                          std::move(logic_manager),
                          std::move(pipeline_manager));
    Presenter presenter(std::move(manager));
}
