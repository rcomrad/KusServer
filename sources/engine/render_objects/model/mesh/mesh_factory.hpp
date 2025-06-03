#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP
#include "glm/vec2.hpp"

#include "mesh.hpp"

namespace kusengine
{
class MeshFactory
{
public:
    static MeshFactory& getInstance();

    template <typename... Args>
    std::shared_ptr<Mesh> createUniversalMesh(Args&&... args);

private:
    std::vector<std::shared_ptr<Mesh>> created_meshes;

    Mesh createUniversalMeshImpl(const glm::vec2& size); // rectangle

    Mesh createUniversalMeshImpl(const glm::vec2& second,
                                 const glm::vec2& third); // triangle

    MeshFactory() = default;
};

template <typename... Args>
std::shared_ptr<Mesh>
MeshFactory::createUniversalMesh(Args&&... args)
{
    Mesh mesh = createUniversalMeshImpl(std::forward<Args>(args)...);

    std::shared_ptr<Mesh> result;

    auto it = std::find_if(created_meshes.begin(), created_meshes.end(),
                           [&mesh](const std::shared_ptr<Mesh>& other)
                           { return *other == mesh; });

    if (it == created_meshes.end())
    {
        result = std::make_shared<Mesh>(mesh);
        created_meshes.emplace_back(result);
    }
    else
    {
        result = *it;
    }

    return result;
}

#define MESH_FACTORY MeshFactory::getInstance()

}; // namespace kusengine

#endif // MESH_FACTORY_HPP
