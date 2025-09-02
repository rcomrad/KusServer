#ifndef COMPLEX_MODEL_HPP
#define COMPLEX_MODEL_HPP

#include <memory>
#include <vector>

#include "model.hpp"

namespace kusengine::render
{
class ComplexModel : public Model
{
public:
    ComplexModel(ModelUpdData::Type mud);

    void addModel(const std::unique_ptr<Model>& model);

    std::unique_ptr<Model> clone() const override;

    void combine(MeshCombiner& mesh_combiner) override;

    void linkUpdData(const std::vector<size_t>& inds,
                     size_t cur_i,
                     std::vector<char>& link_data,
                     int data_size_byte) override;

    size_t getCount() const noexcept override;

private:
    size_t m_count;

    std::vector<std::unique_ptr<Model>> m_models;
};
} // namespace kusengine::render

#endif // COMPLEX_MODEL_HPP
