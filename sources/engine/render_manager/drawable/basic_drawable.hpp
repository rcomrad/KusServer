#ifndef BASIC_DRAWABLE_HPP
#define BASIC_DRAWABLE_HPP

#include <string_view>

#include "engine/render_manager/model/model_storage.hpp"

namespace kusengine
{
namespace render
{
template <typename VertexT_, typename MBDDInterfaceT_>
class BasicDrawable : public MBDDInterfaceT_
{
public:
    using VertexType        = VertexT_;
    using MBDDInterfaceType = MBDDInterfaceT_;

    virtual ~BasicDrawable() = default;

    uint32_t pushModel(ModelStorage<VertexType>& ms);

    void setMesh(const Mesh<VertexType>* const mesh_ptr);

    void setTexture(const Texture* const texture_ptr);

protected:
    Model<VertexType> m_model;
};

template <typename VertexT_, typename MBDDInterfaceT_>
uint32_t
BasicDrawable<VertexT_, MBDDInterfaceT_>::pushModel(
    ModelStorage<VertexType>& ms)
{
    return ms.addModel(m_model);
}

template <typename VertexT_, typename MBDDInterfaceT_>
void
BasicDrawable<VertexT_, MBDDInterfaceT_>::setMesh(
    const Mesh<VertexType>* const mesh_ptr)
{
    m_model.setMesh(mesh_ptr);
}

template <typename VertexT_, typename MBDDInterfaceT_>
void
BasicDrawable<VertexT_, MBDDInterfaceT_>::setTexture(
    const Texture* const texture_ptr)
{
    m_model.setTexture(texture_ptr);
}

}; // namespace render
}; // namespace kusengine

#endif // BASIC_DRAWABLE_HPP
