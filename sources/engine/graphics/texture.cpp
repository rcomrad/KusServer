// #include "texture.hpp"

// #include "engine/graphics/dds_structs.hpp"
// #include "kernel/framework/file_system/include_me.hpp"

// namespace engine::graphics
// {

// Texture::Texture(logic::Device a_logic_device,
//                  const std::string& a_sprite_name,
//                  logic::IncrementBuffer a_buffer)
// {
//     auto texture_as_str = KERNEL.readFileFromDir(a_sprite_name, SPRITE_DIR);
//     auto& texture       = *static_cast<const DDSFile*>(data_as_str.data());

//     uint32_t texture_size = texture.header.width * texture.header.height * 4;
//     a_buffer.push(&texture.data, texture_size);

//     vk::ImageCreateInfo info;
//     info.setMipLevels(1)
//         .setArrayLayers(1)
//         .setImageType(vk::ImageType::e2D)
//         .setFormat(vk::Format::eR8G8B8A8Unorm)
//         .setExtent({data.header.width, data.header.height, 1})
//         .setSamples(vk::SampleCountFlagBits::e1)
//         .setUsage(vk::ImageUsageFlagBits::eTransferDst |
//                   vk::ImageUsageFlagBits::eSampled);

//     a_logic_device.createImageUnique(info);
//     a_logic_device.getMemoryTypeIndex(vk::MemoryPropertyFlagBits::eDeviceLocal);
// }

// } // namespace engine::graphics
