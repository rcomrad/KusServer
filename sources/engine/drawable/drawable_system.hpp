#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/render_objects/model/model_storage.hpp"

#include "drawable.hpp"

namespace kusengine
{
class DrawableSystem
{
public:
    void add(const Drawable* const NO_TEMPARARY);

    void add(const std::vector<std::unique_ptr<Drawable>>* NO_TEMPARARY);

    void generate();

private:
    ModelStorage m_model_storage;

    std::vector<const Drawable*> m_drawables;
};
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_HPP
