#ifndef SIMPLE_MODEL_HPP
#define SIMPLE_MODEL_HPP

#include "engine/render_manager/mesh/mesh.hpp"
#include "model_data/model_upd_matrix.hpp"

#include "model.hpp"

namespace kusengine::render
{
class SimpleModel : public Model
{
public:
    SimpleModel(const std::unique_ptr<ModelUpdData>& model_upd_data =
                    std::make_unique<ModelMatrix>(),
                const IMesh* const mesh = nullptr);

    void setMesh(const IMesh* const mesh) noexcept;

    void setModelUpdData(const std::unique_ptr<ModelUpdData>& model_upd_data);

    std::unique_ptr<Model> clone() const override;

    void combine(MeshCombiner& mesh_combiner) override;

    void linkUpdData(const std::vector<size_t>& inds,
                     size_t cur_i,
                     std::vector<char>& link_data,
                     int data_size_byte) override;

private:
    std::unique_ptr<ModelUpdData> m_model_upd_data;

    const IMesh* m_mesh;
};
} // namespace kusengine::render

#endif // SIMPLE_MODEL_HPP
