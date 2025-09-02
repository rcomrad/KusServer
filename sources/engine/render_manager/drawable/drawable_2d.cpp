#include "drawable_2d.hpp"

namespace kusengine::render
{
Drawable2D::Drawable2D(const std::unique_ptr<Model>& model) : IDrawable(model)
{
}
} // namespace kusengine::render
