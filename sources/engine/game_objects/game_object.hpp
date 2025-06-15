#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <memory>

#include "engine/game_objects/templates/template.hpp"
#include "engine/graphics/drawable/drawable.hpp"

namespace kusengine
{
class GameObject : public Drawable
{
public:
    template <typename DerivedShape>
    GameObject(DerivedShape&& ds)
        : Drawable(std::move(ds))
    {
    }

    virtual void logic() = 0;

protected:
};
}; // namespace kusengine

#endif // GAME_OBJECT_HPP
