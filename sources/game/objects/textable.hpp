#pragma once

#include <string>

#include "gpu/font/font.hpp"
#include "gpu/sprite/draw_task.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::font
{
class FontStorage;
}

namespace game::obj
{

class ObjectInfo;

class Textable
{
public:
    Textable(const ObjectInfo& a_info);
    Textable(Textable&& a_other) noexcept = default;

    void setText(const std::string& a_text);
    void setTextPositionOffset(const gpu::type::Coordinates& a_offset);

    void addTextPresentation(const gpu::font::FontStorage& a_font_storage,
                             std::vector<gpu::sprite::DrawTask>& a_out) const;

private:
    int m_font_id;
    std::string m_text;
    gpu::type::Coordinates m_text_offset;

    // store font id
};

} // namespace game::obj
