#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/render_manager/mesh/mesh.hpp"

namespace kusengine::render
{

class Model
{
public:
    enum class Type
    {
        COMPLEX = 0,
        SIMPLE  = 1
    };

    Model(Type t);

    virtual ~Model() = default;

    void pushTo(std::vector<const Mesh*>& meshes);

    virtual std::pair<const Mesh* const, int> takeMeshes() const = 0;

    // virtual void bind(const vk::CommandBuffer& command_buffer,
    //                   const vk::PipelineLayout& pipelayout) const = 0;

    // virtual void draw(const vk::CommandBuffer& command_buffer,
    //                   const vk::PipelineLayout& pipelayout) const = 0;

private:
    Type m_type;

    int index_of_instance_data_vector = -1;
};

}; // namespace kusengine::render
#endif // MODEL_HPP
