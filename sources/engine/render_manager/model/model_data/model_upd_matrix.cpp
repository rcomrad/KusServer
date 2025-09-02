#include "model_upd_matrix.hpp"

namespace kusengine::render
{

ModelMatrix::ModelMatrix() : ModelUpdData(Type::MATRIX4x4)
{
    m_matrix = std::make_unique<glm::mat4>(1);
}

const char* const
ModelMatrix::get() const noexcept
{
    return reinterpret_cast<const char* const>(m_matrix.get());
}

int
ModelMatrix::byteSize() const noexcept
{
    return sizeof(m_matrix);
}

std::unique_ptr<ModelUpdData>
ModelMatrix::clone() const
{
    std::unique_ptr<ModelUpdData> res = std::make_unique<ModelMatrix>();

    static_cast<ModelMatrix*>(res.get())->m_matrix =
        std::make_unique<glm::mat4>(*(m_matrix.get()));

    return res;
}

void
ModelMatrix::resetBufData()
{
    m_matrix.release();
}

} // namespace kusengine::render
