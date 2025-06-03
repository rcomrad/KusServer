#include "drawable.hpp"

#include "engine/render_objects/model/mesh/mesh_factory.hpp"

#include "drawable_system.hpp"
namespace kusengine
{

Drawable::Drawable() : m_texture_name("empty.png")
{
}

void
Drawable::pushToDrawableSystem(DrawableSystem& sys)
{
}

}; // namespace kusengine
