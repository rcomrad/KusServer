#ifndef DRAWABLE_2D_HPP
#define DRAWABLE_2D_HPP
#include "idrawable.hpp"
namespace kusengine::render
{
class Drawable2D : public IDrawable
{
public:
    Drawable2D() = default;

    Drawable2D(const std::unique_ptr<Model>& model);

private:
    std::unique_ptr<Model> m_model;
};
} // namespace kusengine::render

#endif // DRAWABLE_2D_HPP
