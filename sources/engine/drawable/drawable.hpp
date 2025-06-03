#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "drawable_system.hpp"
#include "shape.hpp"

namespace kusengine
{

class Drawable
{
public:
    virtual ~Drawable() = default;

    Drawable();

    template <typename... MeshFactoryArgs>
    Drawable(std::string_view texture_name, MeshFactoryArgs&&... args);

    void pushToDrawableSystem(DrawableSystem& sys);

protected:
    template <typename... Args>
    void create(Args&&... args);

private:
    std::unique_ptr<Shape> m_shape;
};

template <typename... MeshFactoryArgs>
Drawable::Drawable(std::string_view texture_name, MeshFactoryArgs&&... args)
    : m_texture_name(texture_name)
{
    create(args...);
}

template <typename DerivedShape, typename... MeshFactoryArgs>
void
Drawable::create(MeshFactoryArgs&&... args)
{
    m_shape = std::make_unique<DerivedShape>(args);
}

}; // namespace kusengine

#endif // DRAWABLE_HPP
