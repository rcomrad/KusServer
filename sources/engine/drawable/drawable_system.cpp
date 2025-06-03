#include "drawable_system.hpp"

namespace kusengine
{
void
DrawableSystem::add(const Drawable* const no_temparary_drawable)
{
    if (no_temparary_drawable)
    {
        // no_temparary_drawable->generate();
        m_drawables.emplace_back(no_temparary_drawable);
    }
}

void
DrawableSystem::add(
    const std::vector<std::unique_ptr<Drawable>>* no_temparary_drawables)
{
    m_drawables.reserve(no_temparary_drawables->size() + m_drawables.size());

    for (int i = 0; i < no_temparary_drawables->size(); ++i)
    {
        add(no_temparary_drawables->operator[](i).get());
    }
}

void
DrawableSystem::generate()
{
}

}; // namespace kusengine
