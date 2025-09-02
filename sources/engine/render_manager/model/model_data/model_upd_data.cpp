#include "model_upd_data.hpp"

namespace kusengine::render
{
ModelUpdData::ModelUpdData(Type t) : m_type(t)
{
}

ModelUpdData::Type
ModelUpdData::getType() const noexcept
{
    return m_type;
}

void
ModelUpdData::unlink() noexcept
{
    m_data_link                = nullptr;
    m_is_model_upd_data_linked = false;
}

void
ModelUpdData::link(char* const data) noexcept
{
    m_data_link = data;
    resetBufData();
}

} // namespace kusengine::render
