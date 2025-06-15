#include "shape.hpp"

#include "engine/graphics/models/model/model_storage.hpp"
namespace kusengine
{

Shape::Shape(std::shared_ptr<Mesh> mesh)
{
    m_model.setMesh(mesh);
}

uint32_t
Shape::pushModel(ModelStorage& model_storage)
{
    return model_storage.addModel(m_model);
}

// Shape::Type
// Shape::getType() const noexcept
// {
//     return m_type;
// }
// void
// Shape::setMesh(std::shared_ptr<Mesh> mesh)
// {
//     m_render_object.setMesh(mesh);
// }

// void
// Shape::setPosition(float x, float y)
// {
//     m_render_object.setPosition(x, y);
// }

// void
// Shape::setSize(float x, float y)
// {
//     m_render_object.setSize(x, y);
// }

// void
// Shape::rotate(float angle)
// {
//     m_render_object.setRotation(angle);
// }

void
Shape::loadTexture(std::string_view texture_name)
{
    auto texture_opt = TEXTURE_STORAGE.getTexture(texture_name);

    if (texture_opt.has_value() == false)
    {
        texture_opt = TEXTURE_STORAGE.getTexture("empty.png");
    }

    m_model.setTexture(texture_opt.value());
}

}; // namespace kusengine
