#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "engine/graphics/models/dynamic_data/model_basic_dynamics_data.hpp"

#include "shape.hpp"

namespace kusengine
{

class ModelStorage;

class Drawable : public ModelBasicDynamicsDataInterface
{
public:
    virtual ~Drawable() = default;

    template <typename DerivedShape>
    Drawable(DerivedShape&&);

    void pushModel(ModelStorage& ms);

    virtual void update() = 0;

protected:
    std::unique_ptr<Shape> m_shape;
};

template <typename DerivedShape>
Drawable::Drawable(DerivedShape&& shape)
{
    m_shape = std::make_unique<DerivedShape>(shape);
}

}; // namespace kusengine

#endif // DRAWABLE_HPP
