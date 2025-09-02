#ifndef MODEL_UPD_MATRIX_HPP
#define MODEL_UPD_MATRIX_HPP

#include <glm/mat4x4.hpp>

#include <memory>

#include "model_upd_data.hpp"

namespace kusengine::render
{
class ModelMatrix : public ModelUpdData
{
public:
    ModelMatrix();

    const char* const get() const noexcept override;

    int byteSize() const noexcept override;

    std::unique_ptr<ModelUpdData> clone() const override;

private:
    void resetBufData() override;

    std::unique_ptr<glm::mat4> m_matrix;
};
} // namespace kusengine::render

#endif // MODEL_UPD_MATRIX_HPP
