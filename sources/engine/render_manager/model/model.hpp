#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/render_manager/mesh/mesh_combiner.hpp"
#include "model_data/model_upd_data.hpp"

namespace kusengine::render
{
class Model
{
public:
    virtual ~Model() = default;
    enum class Type
    {
        COMPLEX,
        SIMPLE
    };

    Model(ModelUpdData::Type mud, Type t);

    Type getType() const noexcept;

    ModelUpdData::Type getModelUpdDataType() const noexcept;

    virtual std::unique_ptr<Model> clone() const = 0;

    virtual void combine(MeshCombiner& mesh_combiner) = 0;

    virtual void linkUpdData(const std::vector<size_t>& inds,
                             size_t cur_i,
                             std::vector<char>& link_data,
                             int data_size_byte) = 0;

    virtual size_t getCount() const noexcept;

private:
    Type m_type;

    ModelUpdData::Type m_model_upd_data_type;
};
} // namespace kusengine::render

#endif // MODEL_HPP
