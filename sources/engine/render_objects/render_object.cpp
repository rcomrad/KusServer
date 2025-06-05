#include "render_object.hpp"

namespace kusengine
{

RenderObject::RenderObject(std::shared_ptr<const Mesh> mesh,
                           std::shared_ptr<const Texture> texture)
{
    create(mesh, texture);
}

void
RenderObject::setMesh(std::shared_ptr<const Mesh> mesh)
{
    m_model.setMesh(mesh);
}

void
RenderObject::setTexure(std::shared_ptr<const Texture> texture)
{
    m_model.setTexture(texture);
}

void
RenderObject::create(std::shared_ptr<const Mesh> mesh,
                     std::shared_ptr<const Texture> texture)
{
    setMesh(mesh);
    setTexure(texture);
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
