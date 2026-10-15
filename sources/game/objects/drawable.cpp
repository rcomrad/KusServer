#include "drawable.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "coordinatable.hpp"
#include "object_info.hpp"

game::obj::Drawable::Drawable(const ObjectInfo& a_info) : Coordinatable(a_info)
{
    if (!a_info.sprite_view.has_value())
    {
        THROW("Requers texture for drawable property");
    }
    m_sprite_id = a_info.sprite_view.value().sprite_id;
}

gpu::sprite::DrawTask
game::obj::Drawable::getObjectPresentation() const
{
    const auto& pos = getPosition();
    return gpu::sprite::DrawTask(m_sprite_id, pos);
}
