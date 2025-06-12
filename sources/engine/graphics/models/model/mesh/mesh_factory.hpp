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
    std::shared_ptr<Mesh> createMesh(Args&&... args);

private:
    std::vector<std::shared_ptr<Mesh>> created_meshes;

    Mesh createMeshImpl(const glm::vec2& size); // rectangle

    MeshFactory() = default;
};

template <typename... Args>
std::shared_ptr<Mesh>
MeshFactory::createMesh(Args&&... args)
{
    Mesh mesh = createMeshImpl(std::forward<Args>(args)...);

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
