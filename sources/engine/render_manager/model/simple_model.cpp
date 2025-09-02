#include "simple_model.hpp"

namespace kusengine::render
{

SimpleModel::SimpleModel(const std::unique_ptr<ModelUpdData>& model_upd_data,
                         const IMesh* const mesh)
    : Model(model_upd_data->getType(), Model::Type::SIMPLE)
{
    setModelUpdData(model_upd_data);
    setMesh(mesh);
}

void
SimpleModel::setModelUpdData(
    const std::unique_ptr<ModelUpdData>& model_upd_data)
{
    m_model_upd_data = model_upd_data->clone();
}

void
SimpleModel::setMesh(const IMesh* const mesh) noexcept
{
    m_mesh = mesh;
}

std::unique_ptr<Model>
SimpleModel::clone() const
{
    std::unique_ptr<SimpleModel> res = std::make_unique<SimpleModel>();

    res->m_model_upd_data = m_model_upd_data->clone();

    res->m_mesh = m_mesh;

    return res;
}

void
SimpleModel::combine(MeshCombiner& mesh_combiner)
{
    mesh_combiner.add(m_mesh);
}

void
SimpleModel::linkUpdData(const std::vector<size_t>& inds,
                         size_t cur_i,
                         std::vector<char>& link_data,
                         int data_size_byte)
{
    auto* data = &link_data[inds[cur_i] * data_size_byte];

    *data = *(m_model_upd_data->get());

    m_model_upd_data->link(data);
}

} // namespace kusengine::render
