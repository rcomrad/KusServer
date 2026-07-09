#include "image_loader.hpp"

#include "kernel/framework/include_me.hpp"

#include <filesystem>

#include "gpu/utils/paths.hpp"

#include "dds_structs.hpp"
#include "storage_builder.hpp"

void
gpu::sprite::loadAllImages(StorageBuilder& a_builder)
{
    KERNEL.addDataShortcut(IMAGES_DIR, IMAGES_DIR);
    auto files = KERNEL.getShortcutFileContent(IMAGES_DIR);

    for (auto path : files)
    {
        if (path.extension() == ".dds")
        {
            const auto file_name = path.stem().string();
            LOG_TRACE("Load %s texture", file_name);

            auto file_content = core::FileReader::readBinaryFile(path);
            auto pixel_array  = pixelArrayFromDDS(std::move(file_content));
            a_builder.push(file_name, std::move(pixel_array));
        }
    }
}
