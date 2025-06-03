#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "engine/render_objects/model/mesh/mesh_factory.hpp"
#include "engine/render_objects/render_object.hpp"
#include "engine/textures/texture_storage.hpp"

namespace kusengine
{
class Shape
{
public:
    virtual ~Shape();

    void setTexture(std::string_view texture_name);

    template <typename... Args>
    void setPosition(Args&&... args);

    template <typename... Args>
    void setSize(Args&&... args);

    template <typename... Args>
    void rotate(Args&&... args);

    template <typename... Args>
    Shape(std::string_view texture_name, Args&&... args);

protected:
    template <typename... Args>
    void create(Args&&... args);

private:
    std::string m_texture_name;

    RenderObject m_render_object;
};

template <typename... Args>
Shape::Shape(std::string_view texture_name, Args&&... args)
    : m_texture_name(texture_name)
{
    create(args...);
}

template <typename... Args>
void
Shape::create(Args&&... args)
{
    auto mesh        = MESH_FACTORY.createUniversalMesh(args...);
    auto texture_opt = TEXTURE_STORAGE.getTexture(m_texture_name);

    if (texture_opt.has_value() == false)
    {
        m_texture_name = "empty.png";
        texture_opt    = TEXTURE_STORAGE.getTexture("empty.png");
    }

    m_render_object.create(mesh, texture_opt.value());
}

template <typename... Args>
void
Shape::setPosition(Args&&... args)
{
    m_render_object.setPosition(std::forward<Args>(args)...);
}

template <typename... Args>
void
Shape::setSize(Args&&... args)
{
    m_render_object.setSize(std::forward<Args>(args)...);
}

template <typename... Args>
void
Shape::rotate(Args&&... args)
{
    m_render_object.setRotation(std::forward<Args>(args));
}
}; // namespace kusengine

#endif // SHAPE_HPP
