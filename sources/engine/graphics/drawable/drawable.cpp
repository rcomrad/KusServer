#include "drawable.hpp"

#include "engine/graphics/models/model/mesh/mesh_factory.hpp"

#include "drawable_system.hpp"
namespace kusengine
{

void
Drawable::pushModel(ModelStorage& model_storage)
{
    m_shape->pushModel(model_storage);
}

}; // namespace kusengine
