#include "drawable.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "coordinatable.hpp"
#include "object_info.hpp"

game::Drawable::Drawable(const ObjectInfo& a_info)
{
    if (!a_info.sprite_view.has_value())
    {
        THROW("Requers texture for drawable property");
    }
    m_sprite_id = a_info.sprite_view.value();
}

gpu::sprite::DrawTask
game::GameObject::getObjectPresentation() const
{
    const auto& pos = dynamic_cast<Coordinatable&>(*this).getPosition();
    return gpu::sprite::DrawTask(m_sprite_id, pos);
}
