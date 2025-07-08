#include "model_manager.hpp"

#include "engine/json_parser/model_2d_parser.hpp"
#include "engine/render_manager/mesh/mesh_manager.hpp"
#include "utility/file_system/path_storage.hpp"

namespace kusengine::render
{

void
ModelManager::load(const DescriptorManager& desc_manager)
{
    m_resource_manager.load(desc_manager);

    auto models_data = json_parser::parseModels2D();

    for (auto& model_data : models_data)
    {
        model_2d_p1uv1_storage[model_data.name] =
            m_resource_manager.meshes().getMesh<Vertex2DP1UV1>(model_data.mesh);

        model_2d_p1uv1_storage[model_data.texture] =
            m_resource_manager.textures().getTexture(model_data.name);
    }
}

const Model<Vertex2DP1UV1>* const
ModelManager::getModelImpl(const std::string& model_name,
                           ChooseModelType<Vertex2DP1UV1> cmt)
{
    return &model_2d_p1uv1_storage[model_name];
}

const Model<Vertex3DP1UV1>* const
ModelManager::getModelImpl(const std::string& model_name,
                           ChooseModelType<Vertex3DP1UV1> cmt)
{
    return &model_3d_p1uv1_storage[model_name];
}

} // namespace kusengine::render
