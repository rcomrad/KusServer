#include "textable.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/font/font_storage.hpp"

#include "coordinatable.hpp"
#include "object_info.hpp"

game::Textable::Textable(const ObjectInfo& a_info)
{
    if (!a_info.font_id.has_value())
    {
        THROW("Requers fony for texable property");
    }

    m_font_id     = a_info.font_id.value_or(-1);
    m_text        = a_info.text.value_or("");
    m_text_offset = gpu::type::Coordinates(0, 0);
}

void
game::GameObject::setText(const std::string& a_text)
{
    m_text = a_text;
}

void
game::GameObject::setTextPositionOffset(const gpu::type::Coordinates& a_offset)
{
    m_text_offset = a_offset;
}

void
game::GameObject::addTextPresentation(
    const gpu::font::FontStorage& a_font_storage,
    std::vector<gpu::sprite::DrawTask>& a_out) const
{
    Drawable::addPresentation(a_gpu_resources, a_draw_tasks);
    const auto& pos = dynamic_cast<Coordinatable&>(*this).getPosition();
    a_gpu_resources.writeText(m_text, pos + m_text_offset, m_font_id, a_out);
}
