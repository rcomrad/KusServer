#include "drawable.hpp"

#include "engine/render_objects/model/mesh/mesh_factory.hpp"

#include "drawable_system.hpp"
namespace kusengine
{

void
Drawable::pushModel(ModelStorage& model_storage)
{
    m_shape->pushModel(model_storage);
}

}; // namespace kusengine
