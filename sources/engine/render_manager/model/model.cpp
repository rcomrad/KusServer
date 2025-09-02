#include "model.hpp"

namespace kusengine::render
{
Model::Model(ModelUpdData::Type mud, Type t)
    : m_type(t), m_model_upd_data_type(mud)
{
}

Model::Type
Model::getType() const noexcept
{
    return m_type;
}

ModelUpdData::Type
Model::getModelUpdDataType() const noexcept
{
    return m_model_upd_data_type;
}

size_t
Model::getCount() const noexcept
{
    return 1;
}

} // namespace kusengine::render
