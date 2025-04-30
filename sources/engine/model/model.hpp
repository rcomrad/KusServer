#ifndef MODEL_HPP
#define MODEL_HPP

#include "mesh.hpp"
#include "vertex.hpp"

namespace kusengine
{
class Model
{
public:
    void create();

    const Mesh<UniversalVertex>& getMesh() const;

private:
    Mesh<UniversalVertex> m_mesh;
};
}; // namespace kusengine

#endif // MODEL_HPP
