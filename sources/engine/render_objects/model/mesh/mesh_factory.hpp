#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP
#include "engine/render_objects/model/vertex/vertex.hpp"

#include "mesh.hpp"

namespace kusengine
{
class MeshFactory
{
public:
    static MeshFactory& getInstance();

    Mesh createUniversalRectangleMesh(const MyVec2& position,
                                      const MyVec2& size);

    Mesh createUniversalTriangleMesh(const MyVec2& first,
                                     const MyVec2& second,
                                     const MyVec2& third);

private:
    MeshFactory() = default;
};

#define MESH_FACTORY MeshFactory::getInstance()

}; // namespace kusengine

#endif // MESH_FACTORY_HPP
