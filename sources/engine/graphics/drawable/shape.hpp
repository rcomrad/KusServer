#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "engine/graphics/models/model/mesh/mesh_factory.hpp"
#include "engine/graphics/models/model/model.hpp"
#include "engine/graphics/textures/texture_storage.hpp"
namespace kusengine
{

class ModelStorage;

class Shape
{
public:
    virtual ~Shape() = default;

    Shape(std::shared_ptr<Mesh> mesh);

    void loadTexture(std::string_view texture_name);

    void pushModel(ModelStorage&);

private:
    Model m_model;
};

// template <typename... Args>
// Shape::Shape(std::string_view texture_name, Args&&... args)
// {
//     create(texture_name, args...);
// }

// template <typename... MeshFactoryArgs>
// void
// Shape::create(std::string_view texture_name, MeshFactoryArgs&&... args)
// {
//     auto mesh        = MESH_FACTORY.createUniversalMesh(args...);
//     auto texture_opt = TEXTURE_STORAGE.getTexture(texture_name);

//     if (texture_opt.has_value() == false)
//     {
//         texture_opt = TEXTURE_STORAGE.getTexture("empty.png");
//     }

//     m_render_object.create(mesh, texture_opt.value());
// }

// template <typename... Args>
// void
// Shape::setPosition(Args&&... args)
// {
//     m_render_object.setPosition(std::forward<Args>(args)...);
// }

// template <typename... Args>
// void
// Shape::setSize(Args&&... args)
// {
//     m_render_object.setScale(std::forward<Args>(args)...);
// }

// template <typename... Args>
// void
// Shape::rotate(Args&&... args)
// {
//     m_render_object.setRotation(std::forward<Args>(args));
// }
}; // namespace kusengine

#endif // SHAPE_HPP
