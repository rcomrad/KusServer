#include "font_loader.hpp"

#include "kernel/framework/include_me.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

#include "gpu/utils/paths.hpp"

#include "font_info.hpp"
#include "font_storage_builder.hpp"

// TODO: make all loaders like this, possible add polymorphism

void
gpu::font::loadAllFonts(FontStorageBuilder& a_builder)
{
    SCOPED_TRACE_CREATE("load all fonts")

    KERNEL.addDataShortcut(FONTS_DIR, FONTS_DIR);
    auto files = KERNEL.getShortcutFileContent(FONTS_DIR);

    std::unordered_map<std::string, std::filesystem::path> m_font_files;
    for (auto path : files)
    {
        if (path.extension() == ".ttf")
        {
            const auto file_name = path.stem().string();
            LOG_TRACE("Located %s font file", file_name);
            m_font_files.emplace(file_name, path);
        }
    }

    auto map_path = KERNEL.getShortcut(FONTS_DIR, "map.txt");
    auto font_map = KERNEL.readStructMap<FontInfo>(map_path);
    for (auto& [nickname, info] : font_map)
    {
        auto it = m_font_files.find(info.name);
        if (it == m_font_files.end())
        {
            THROW("No '%s' font file fonud", info.name);
        }
        a_builder.push(nickname, info, it->second);
    }
}
