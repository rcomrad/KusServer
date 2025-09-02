#include "complex_model.hpp"

#include <iostream>
namespace kusengine::render
{
ComplexModel::ComplexModel(ModelUpdData::Type mud)
    : Model(mud, Model::Type::COMPLEX), m_count(0)
{
}

void
ComplexModel::addModel(const std::unique_ptr<Model>& model)
{
    if (model->getModelUpdDataType() != getModelUpdDataType())
    {
        std::cout << "different model up data types\n";
        return;
    }
    m_count += model->getCount();
    m_models.emplace_back(model->clone());
}

std::unique_ptr<Model>
ComplexModel::clone() const
{
    std::unique_ptr<ComplexModel> res =
        std::make_unique<ComplexModel>(getModelUpdDataType());

    res->m_count = m_count;

    for (size_t i = 0; i < m_models.size(); ++i)
    {
        res.get()->addModel(m_models[i]->clone());
    }
    return res;
}

void
ComplexModel::combine(MeshCombiner& mesh_combiner)
{
    for (int i = 0; i < m_models.size(); ++i)
    {
        m_models[i]->combine(mesh_combiner);
    }
}

void
ComplexModel::linkUpdData(const std::vector<size_t>& inds,
                          size_t cur_i,
                          std::vector<char>& link_data,
                          int data_size_byte)
{
    for (int i = cur_i; i < m_models.size(); ++i, ++cur_i)
    {
        m_models[i]->linkUpdData(inds, cur_i, link_data, data_size_byte);
    }
}

size_t
ComplexModel::getCount() const noexcept
{
    return m_count;
}

} // namespace kusengine::render
