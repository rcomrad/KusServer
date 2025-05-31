#include "drawable.hpp"

namespace kusengine
{
Drawable::Drawable(ShapeType shape_type) : m_shape_type(shape_type)
{
}

// ------- RECTANGLE ----------- //

void
Drawable::createImpl(const MyVec2& position, const MyVec2& size)
{
    m_render_object = std::make_unique<RenderObject>();
}

// ------- CIRCLE ----------- //

void
Drawable::createImpl(const MyVec2&, float radius, float freq)
{
}

// ------- TRIANGLE ----------- //

void
Drawable::createImpl(const MyVec2&, const MyVec2&, const MyVec2&)
{
}

}; // namespace kusengine
