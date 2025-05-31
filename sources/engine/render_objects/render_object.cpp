#include "render_object.hpp"

namespace kusengine
{

RenderObject::RenderObject(std::shared_ptr<const Mesh> mesh,
                           std::shared_ptr<const Texture> texture)
    : dynamics_data_ptr(nullptr)
{
    m_model.setMesh(mesh);
    m_model.setTexture(texture);
}

// bool
// RenderObject::compareModelData(const Model& other_model) const
// {
// }

void
RenderObject::linkDynamicsData(ObjectDynamicsData* const dd_ref)
{
    dynamics_data_ptr = dd_ref;
}

void
RenderObject::setDynamicsData(const ObjectDynamicsData& dd)
{
    if (dynamics_data_ptr) *dynamics_data_ptr = dd;
}

int
RenderObject::pushModelData(
    std::vector<std::pair<Model, uint32_t>>& models) const
{
    auto it = std::find_if(models.begin(), models.end(),
                           [this](const std::pair<Model, uint32_t>& other)
                           { return this->m_model.compareData(other.first); });

    int index = it - models.begin();

    if (it == models.end())
    {
        models.emplace_back(m_model, 1u);
    }
    else
    {
        it->second += 1;
    }
    return index;
}

}; // namespace kusengine
