#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/render_manager/mesh/mesh.hpp"

#include "bind_info.hpp"

namespace kusengine::render
{

template <typename Vertex_t_, typename InstanceData_t_>
class Model // Composite class
{
public:
    enum class Type
    {
        COMPLEX = 0,
        SIMPLE  = 1
    };

    using Vertex_t       = Vertex_t_;
    using InstanceData_t = InstanceData_t_;

    Model(Type t);

    Model() = default;

    virtual ~Model() = default;

    virtual void pushTo(
        std::vector<std::pair<const Mesh<Vertex_t>*, int>>& meshes) const = 0;

private:
    Type m_type;

    InstanceData_t* link_to_inst_data = nullptr;
};

template <typename Vertex_t, typename InstanceData_t>
Model<Vertex_t, InstanceData_t>::Model(Type t) : m_type(t)
{
}

}; // namespace kusengine::render
#endif // MODEL_HPP
