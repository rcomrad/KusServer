#ifndef BASIC_DRAWABLE_HPP
#define BASIC_DRAWABLE_HPP

#include <string_view>

#include "engine/render_manager/model/model_storage.hpp"

namespace kusengine
{
namespace render
{
template <typename VertexType_, typename MBDDInterfaceType_>
class BasicDrawable : public MBDDInterfaceType_
{
public:
    using VertexType        = VertexType_;
    using MBDDInterfaceType = MBDDInterfaceType_;

    virtual ~BasicDrawable() = default;

    BasicDrawable() = default;

    uint32_t pushModel(ModelStorage<VertexType>& ms);

    void setMesh(const Mesh<VertexType>* const mesh_ptr);

    void setTexture(const Texture* const texture_ptr);

protected:
    Model<VertexType> m_model;
};

template <typename VertexType_, typename MBDDInterfaceType_>
uint32_t
BasicDrawable<VertexType_, MBDDInterfaceType_>::pushModel(
    ModelStorage<VertexType>& ms)
{
    ms.addModel(m_model);
}

template <typename VertexType_, typename MBDDInterfaceType_>
void
BasicDrawable<VertexType_, MBDDInterfaceType_>::setMesh(
    const Mesh<VertexType>* const mesh_ptr)
{
    m_model.setMesh(mesh_ptr);
}

template <typename VertexType_, typename MBDDInterfaceType_>
void
BasicDrawable<VertexType_, MBDDInterfaceType_>::setTexture(
    const Texture* const texture_ptr)
{
    m_model.setTexture(texture_ptr);
}

}; // namespace render
}; // namespace kusengine

#endif // BASIC_DRAWABLE_HPP
