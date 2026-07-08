#include "freetype_instance.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

gpu::font::FreeTypeInstance::FreeTypeInstance()
{
    auto error = FT_Init_FreeType(&m_ft_lib);
    if (error)
    {
        THROW("Unable to initialize FreeType library");
    }
}

gpu::font::FreeTypeInstance::~FreeTypeInstance()
{
    FT_Done_FreeType(m_ft_lib);
}

FT_Face
gpu::font::FreeTypeInstance::createFace(const std::string& a_font_name)
{
    FT_Face result;
    auto error = FT_New_Face(m_ft_lib, a_font_name.c_str(), 0, &result);

    if (error == FT_Err_Unknown_File_Format)
    {
        THROW("The font file could be opened and read, but it appears that its "
              "font format is unsupported");
    }
    else if (error)
    {
        THROW("The font file could not be opened or read");
    }

    return result;
}
