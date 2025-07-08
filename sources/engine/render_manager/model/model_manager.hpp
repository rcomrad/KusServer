#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP
#include <unordered_map>

#include "engine/render_manager/resource_manager/resource_manager.hpp"
#include "engine/render_manager/vertex/vertex_usings.hpp"

#include "model.hpp"

namespace kusengine::render
{

template <typename ModelType>
struct ChooseModelType
{
};

class ModelManager
{
public:
    template <typename ModelType>
    const ModelType* const getModel(const std::string& model_name);

    void load(const DescriptorManager& desc_manager);

private:
    ResourceManager m_resource_manager;

    const Model<Vertex2DP1UV1>* const getModelImpl(
        const std::string& model_name,
        ChooseModelType<Vertex2DP1UV1>);

    const Model<Vertex3DP1UV1>* const getModelImpl(
        const std::string& model_name,
        ChooseModelType<Vertex3DP1UV1>);

    // storages

    std::unordered_map<std::string, Model<Vertex2DP1UV1>>
        model_2d_p1uv1_storage;

    std::unordered_map<std::string, Model<Vertex3DP1UV1>>
        model_3d_p1uv1_storage;
};

template <typename ModelType>
const ModelType* const
ModelManager::getModel(const std::string& model_name)
{
    return getModelImpl(model_name, ChooseModelType<ModelType>{});
}

} // namespace kusengine::render

#endif // MODEL_MANAGER_HPP
