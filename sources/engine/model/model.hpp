#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/model/mesh/mesh.hpp"
#include "engine/model/vertex/vertex.hpp"

namespace kusengine
{
class Model
{
public:
    void setMesh(const Mesh<UniversalVertex>& mesh);
    void setMesh(Mesh<UniversalVertex>&& mesh);

    const Mesh<UniversalVertex>& getMesh() const;

private:
    Mesh<UniversalVertex> m_mesh;
};

}; // namespace kusengine

#endif // MODEL_HPP
